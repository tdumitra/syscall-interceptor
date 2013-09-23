/* (c) Tudor Dumitras, 2006-2007 */
#include "interceptor.h"
#include "interc_defs.h"
#include "tracec.h"

//extern "C" void init_fptrs() throw();

InterceptorState::InterceptorState() 
{
  /* Initialize the pointers to the orginal versions 
     of the intercepted functions */
  FunctionPointers::init_fptrs();
  
  /* Initialize the tracing */
  init_trace();
}

InterceptorState::~InterceptorState()
{
  /* nothing to do */
}

