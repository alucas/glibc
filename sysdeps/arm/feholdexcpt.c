/* Store current floating-point environment and clear exceptions.
   Copyright (C) 1997-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#include <fenv.h>
#include <fpu_control.h>
#include <arm-features.h>


int
feholdexcept (fenv_t *envp)
{
  fpu_control_t fpscr;

  /* Fail if a VFP unit isn't present.  */
  if (!ARM_HAVE_VFP)
    return 1;

  _FPU_GETCW (fpscr);
  envp->__cw = fpscr;

  /* Now set all exceptions to non-stop.  */
  fpscr &= ~(FE_ALL_EXCEPT << FE_EXCEPT_SHIFT);

  /* And clear all exception flags.  */
  fpscr &= ~FE_ALL_EXCEPT;

  _FPU_SETCW (fpscr);
  return 0;
}

libm_hidden_def (feholdexcept)
