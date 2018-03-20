/* Subroutines used for code generation for Fusion-Core.
   Contributed by Dylan Wadler (dylan@fusion-core.org).
   Based on RISC-V target for GNU compiler.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "regs.h"
#include "hard-reg-set.h"
#include "insn-config.h"
#include "conditions.h"
#include "insn-attr.h"
#include "recog.h"
#include "output.h"
#include "hash-set.h"
#include "machmode.h"
#include "vec.h"
#include "double-int.h"
#include "input.h"
#include "alias.h"
#include "symtab.h"
#include "wide-int.h"
#include "inchash.h"
#include "tree.h"
#include "fold-const.h"
#include "varasm.h"
#include "stringpool.h"
#include "stor-layout.h"
#include "calls.h"
#include "function.h"
#include "hashtab.h"
#include "flags.h"
#include "statistics.h"
#include "real.h"
#include "fixed-value.h"
#include "expmed.h"
#include "dojump.h"
#include "explow.h"
#include "memmodel.h"
#include "emit-rtl.h"
#include "stmt.h"
#include "expr.h"
#include "insn-codes.h"
#include "optabs.h"
#include "libfuncs.h"
#include "reload.h"
#include "tm_p.h"
#include "ggc.h"
#include "gstab.h"
#include "hash-table.h"
#include "debug.h"
#include "target.h"
#include "target-def.h"
#include "common/common-target.h"
#include "langhooks.h"
#include "dominance.h"
#include "cfg.h"
#include "cfgrtl.h"
#include "cfganal.h"
#include "lcm.h"
#include "cfgbuild.h"
#include "cfgcleanup.h"
#include "predict.h"
#include "basic-block.h"
#include "bitmap.h"
#include "regset.h"
#include "df.h"
#include "sched-int.h"
#include "tree-ssa-alias.h"
#include "internal-fn.h"
#include "gimple-fold.h"
#include "tree-eh.h"
#include "gimple-expr.h"
#include "is-a.h"
#include "gimple.h"
#include "gimplify.h"
#include "diagnostic.h"
#include "target-globals.h"
#include "opts.h"
#include "tree-pass.h"
#include "context.h"
#include "hash-map.h"
#include "plugin-api.h"
#include "ipa-ref.h"
#include "cgraph.h"
#include "builtins.h"
#include "rtl-iter.h"

/* Fusion-Core implementation of TARGET_RETURN_IN_MEMORY */
static bool
fusion_return_in_memory(const_tree type, const_tree fndecl ATTRIBUTE_UNUSED){
	const HOST_WISE_INT size = int_size_in_bytes(type);
	return (size == -1 || size > 2 * UNITS_PER_WORD);
}

/* Initialize GCC target structure */

#undef 	TARGET_PROMOTE_FUNCTION_ARGS
#define TARGET_PROMOTE_FUNCTION_ARGS 		hook_bool_const_tree_true
#undef	TARGET_PROMOTE_FUNCTION_RETURN
#define	TARGET_PROMOTE_FUNCTION_RETURN 		hook_bool_const_tree_true
#undef	TARGET_PROMOTE_PROTOTYPES
#define	TARGET_PROMOTE_PROTOTYPES			hook_bool_const_tree_true
#undef	TARGET_RETURN_IN_MEMORY				
#define	TARGET_RETURN_IN_MEMORY				fusion_return_in_memory;
