#!/usr/bin/perl

# (c) Tudor Dumitras, 2006-2007

# This script takes as input a set of system-call declarations 
# and generates an interceptor based on library interposition.
# The modified functions output the function parameters and 
# return values to a trace logger.


##############################################################
# CONFIGURATION SETTINGS
##############################################################

my $FUN_DECLS    = 'fun_decls.hpp';          # input file

my $HEADER       = 'interc_defs.h';          # output files
my $NEW_FUN      = 'modified_fun.cpp';
my $FP           = 'function_pointers.cpp';





##############################################################
# MISC SETTINGS
##############################################################

# Name of the class that encapsulates the function pointers
my $FPTR_CLASS  = 'FunctionPointers';

# Temporary file names
my $HEADER_S1   = 'h_s1.tmp';
my $HEADER_S2   = 'h_s2.tmp';
my $HEADER_S3   = 'h_s3.tmp';
my $HEADER_S4   = 'h_s4.tmp';
my $FP_S1       = 'f_s1.tmp';
my $FP_S2       = 'f_s2.tmp';
my $NEW_FUN_S1  = 'n_s1.tmp';

# Program options
my $opt_x       = 0;    # examine the read() and write() buffers


##############################################################
# PROGRAM CODE
##############################################################

# This script generates three files: $HEADER, $NEW_FUN and $FP.
#
# $HEADER:   a C/C++ header file that declares and defines the 
#            inline wrappers for the default system calls.
#            $HEADER has 4 sections:
#  1. Headers required by the intercepted system calls
#  2. Declarations of the default system-call wrappers
#     (e.g., real_socket)
#  3. A C++ class encapsulating the pointers to the default
#     system calls
#  4. Definitions of the default system-call wrappers (they 
#     reference the function pointers from sec. 3)
#
# $FP:       implementation of the C++ class declared
#            in sec. 3 of $HEADER. This file has 2 sections:
#  1. Define the function pointers, which are members of the 
#     class (there's one for each system call intercepted)
#  2. Define a method that initializes the function pointers
#     using dlsym(). This method must be called before any 
#     of the intercepted functions.
#
# $NEW_FUN:  a C++ source file that declares the modified 
#            system calls. This function has only 1 section.
#  
# The interceptor also uses 5 more files that do not change:
# interceptor.h, interceptorstate.cpp, tracec.h, tracec.cpp
# and Makefile. trace_logger.cpp is a standalone program 
# that receives messages from the interceptor over a named
# pipe and prints them to stdout.


# Parse arguments
foreach (@ARGV) {
    usage()      if (m/-h/);
    $opt_x = 1   if (m/-x/);
}

# Open the input file
open (INFILE, "<$FUN_DECLS") or die "Can't open $FUN_DECLS: $!";

# Open temporary files, one for each section of the files to 
# generate
open (H_S1, ">$HEADER_S1") or die "Can't open $HEADER_S1: $!";
open (H_S2, ">$HEADER_S2") or die "Can't open $HEADER_S2: $!";
open (H_S3, ">$HEADER_S3") or die "Can't open $HEADER_S3: $!";
open (H_S4, ">$HEADER_S4") or die "Can't open $HEADER_S4: $!";
open (F_S1, ">$FP_S1") or die "Can't open $FP_S1: $!";
open (F_S2, ">$FP_S2") or die "Can't open $FP_S2: $!";
open (N_S1, ">$NEW_FUN_S1") or die "Can't open $NEW_FUN_S1: $!";


while (<INFILE>) {
    my $line = $_;

    # Elide C and C++ comments
    $line =~ s/\/\*.*\*\///;
    $line =~ s/\/\/.*$//;

    # Skip empty lines
    next unless $line =~ m/\S/;

    # Read the headers required and write them to the first 
    # section of $HEADER
    if ($line =~ m/^\#/) {
	print H_S1 $line;
	next;
    }
    
    # Read the declarations of the system calls to be 
    # intercepted and parse them into the following tokens:
    # - return type (may be void)
    # - function name
    # - parameter types (may be void)
    # - parameter names
    # - throw declaration (may be empty)
    $line =~ m/
	^(.*[\s\*])                          # return type
	(\w+)                                # name 
	\((.+?)\)                            # args
	\s*(throw.*|\s*);                    # throw()
    /x;
    my $rettype = trim($1);
    my $fname = trim($2);
    my $args = trim($3);
    my $throw = trim($4);
    my @args_list = split(/,/, $args);       # split arg list
    my @arg_types;
    my @arg_names;
    foreach (@args_list) {
	$_ =~ m/
	    (^void$ |                        # void or
	     ^(.*[\s\*]) (\w+) (\[\w*\])*$)  # type name[sz]
	    /x;
	if ($1 eq 'void') {
	    push (@arg_types, 'void');
	    push (@arg_names, '');
	} else {
	    push (@arg_types, $4 ? trim($2) . '*' : trim($2));
	    push (@arg_names, trim($3));
	}
    }
    #print "$line$rettype\n$fname\n$args\n@arg_types\n@arg_names\n$throw\n\n";

    # Write declaration of real_* function in sec. 2 of 
    # $HEADER
    my $new_line = $line;
    my $new_fname = "real_$fname";
    $new_line =~ s/$fname/$new_fname/;
    print H_S2 "extern \"C\" $new_line";

    # Write fptr_* member of the class in sec. 3 of 
    # $HEADER (using retval, name, param. types)
    my $paramz = join(', ', @arg_types);
    print H_S3 "  static $rettype (*fptr_$fname) ($paramz);\n";

    # Write fptr_* definition in sec. 1 of $FP
    my $fptr_full_name = "$FPTR_CLASS" . "::fptr_$fname";
    print F_S1 "$rettype (*$fptr_full_name)($paramz) = NULL;\n";

    # Write initialization code of fptr_* member inside
    # init_fptrs() method in sec. 2 of $FP
    my $exit_call = $fname eq 'exit' ? '_exit' : 'real_exit';
    print F_S2 <<EOF;

  /* $fname() fptr */
  if (  (fptr_$fname = 
	 ($rettype (*)($paramz)) 
	 dlsym(RTLD_NEXT, "$fname")) 
	== NULL) {
    /* Missing library; cannot continue */
    $exit_call(-1);
  }
EOF

    # Write body of real_* function in sec. 4 of $HEADER
    my $argz = join(', ', @arg_names);
    if ($rettype eq 'void') {
	print H_S4 <<EOF

inline
void 
real_$fname($args) $throw
{
  (void)(*$fptr_full_name) ($argz);
}
EOF
    } else {
	print H_S4 <<EOF

inline 
$rettype 
real_$fname($args) $throw
{
  $rettype retval;
  retval = (*$fptr_full_name) ($argz);
  return retval;
}
EOF
    }

    # Write body of interception function in $NEW_FUN
    my @fmt;                # format for printing the arguments
    foreach (@arg_types) {
        push (@fmt, printf_format($_));
    }
    my $format1 = join (', ', @fmt);     # for printout before call
    $opt_x && $fname eq 'write' &&   $format1 =~ s/%p/%s/;
    my $format2 = $format1;              # for printoug after call
    $format2 =~ s/%s/%p/;
    $opt_x && $fname eq 'read' &&    $format2 =~ s/%p/%s/;
    $format3 = printf_format($rettype);  # for the return value
    $coma = $args eq 'void' ? '' : ',';

    if ($rettype eq 'void') {
        # Generate the body of a function that does not return anything
        print N_S1 <<EOF;

extern "C" 
void
$fname($args) $throw
{
  print_trace ("%*s$fname($format1)...\\n", indent, ""$coma
	       $argz);
  indent+=2;

  /* call the real $fname function */
  real_$fname ($argz);

  indent-=2;
  print_trace ("%*s$fname($format2)\\n", indent, ""$coma 
	       $argz);
}
EOF
    } else {
        # Generate the body of a function that returns a value
        print N_S1 <<EOF;

extern "C" 
$rettype
$fname($args) $throw
{
  $rettype retval;

  print_trace ("%*s$fname($format1)=...\\n", indent, ""$coma
	       $argz);
  indent+=2;

  /* call the real $fname function */
  retval = real_$fname ($argz);

  indent-=2;
  print_trace ("%*s$fname($format2)=$format3\\n", indent, ""$coma 
	       $argz, retval);

  return retval;
}
EOF
}
}

close INFILE;
close H_S1,H_S2,H_S3,H_S4,F_S1,F_S2,N_S1;

# Combine sections 1,2,3,4 of $HEADER
system ("cat " .
	"stubs/h.pre " .
	"stubs/h_s1.pre $HEADER_S1 stubs/h_s1.post " .
	"stubs/sep " .
	"stubs/h_s2.pre $HEADER_S2 stubs/h_s2.post " .
	"stubs/sep " .
	"stubs/h_s3.pre $HEADER_S3 stubs/h_s3.post " .
	"stubs/sep " .
	"stubs/h_s4.pre $HEADER_S4 stubs/h_s4.post " .
	"stubs/h.post " .
	"> $HEADER");

# Combine sections 1,2 of $FP
system ("cat " .
	"stubs/f.pre " .
	"stubs/f_s1.pre $FP_S1 stubs/f_s1.post " .
	"stubs/sep " .
	"stubs/f_s2.pre $FP_S2 stubs/f_s2.post " .
	"stubs/f.post " .
	"> $FP");

# Combine sections 1 of $NEW_FUN
system ("cat " .
	"stubs/n.pre " .
	"stubs/n_s1.pre $NEW_FUN_S1 stubs/n_s1.post " .
	"stubs/n.post " .
	"> $NEW_FUN");

# Remove temporary files
system ("rm $HEADER_S1 $HEADER_S2 $HEADER_S3 $HEADER_S4 $FP_S1 $FP_S2 $NEW_FUN_S1");

# done



##############################################################
# SUBROUTINES
##############################################################

# Return the format specifier that corresponds to a type
sub printf_format 
{
    return '' unless m/\S/;    
    return '' if m/^void$/;    

    my $spec;
    if (m/int/) {
	$spec = '%d';
    } elsif (m/unsigned/) {
	$spec = '%u';
    } elsif (m/char\s+\*/) {
	$spec = '%s';
    } elsif (m/\*/) {
	$spec = '%p';
    } elsif (m/char/) {
	$spec = '%c';
    } elsif (m/double/ || m/float/) {
	$spec = '%f';
    } else {
	$spec = '%d';
    }

    return $spec;
}

# Remove whitespace from the start and end of the string
sub trim($)
{
    my $string = shift;
    $string =~ s/^\s+//;
    $string =~ s/\s+$//;
    return $string;
}

# Usage of this program
sub usage 
{
    print <<EOF;
$0 -- Generates a system-call interceptor using the 
declarations from $FUN_DECLS. Possible switches:

 -h    : this message
 -x    : examine the contents of the read and write buffers

EOF
exit(0);
}
