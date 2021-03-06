<h2>New in release 0.7.3</h2>

This release is primarily a bug-fix release.  The problems fixed
include installation problems on Windows, some problems with the
profiler, and compatibility with GNU Make versions >= 3.76.
But as well as bug fixes, there are a few minor improvements:

<ul>
<li> The profiler now allows you to merge profiling data from multiple runs.<p>

  There's a new script `mprof_merge_runs' to support this.
  See the "Profiling" section of the Mercury User's Guide,
  or the man page for `mprof_merge_runs'.<p>

<li> Termination analysis no longer uses the `lp_solve' package,
     so we have removed it from the distribution.<p>
  
  This avoids some portability problems and some copyright issues
  (the `lp_solve' package had a quite restrictive license).<p>

<li> We've fixed one of the limitations: unique mode declarations
     no longer have to precede non-unique mode declarations.<p>
</ul>

<h2>New in release 0.7.2</h2>

We have split the distribution into two parts, a `core' part and an
`extras' part.  We still recommend that people get both parts.

<h3>Changes to the Mercury language</h3>

<ul>
<li> We have added support for constraint handling.<p>

  To support constraint handling, we've made the mode system a bit
  more flexible.  There is a new inst `any' for variables whose value
  is unknown but which may have constraints on them.<p>

  The support for `any' insts is not 100% complete; in particular, we
  do not support passing values of inst `free' where values of inst
  `any' are expected, so sometimes you have to explicitly call a predicate
  to initialize a free variable to inst `any'.  Also the Mercury language
  reference manual does not yet contain any documentation on `any'
  insts.<p>

  The `extras' distribution includes packages for doing constraint
  solving on (a) floating point numbers and (b) terms containing
  Prolog-style variables.  See below.<p>

<li> The C interface now includes generalized trailing support.<p>

  The compiler has a new set of grades `*.tr' (e.g. `asm_fast.gc.tr')
  which provide support for trailing.  They could be used by predicates or
  functions defined using the C interface to perform such things as
  constraint solving, backtrackable destructive update, or even automatic
  unwinding of database transactions on backtracking.  See the
  documentation in the "Trailing" section of the Mercury language
  reference manual (it's at the end of the "C interface" section,
  which is in the chapter on "Pragmas").<p>

<li> We now support user-defined equality predicates.<p>

  See the Mercury language reference manual for details.<p>

  However, until we have support for type classes (coming soon :-),
  you will probably run into trouble if you try to use compare/3,
  write/1, functor/2, etc., on a type with user-defined equality.
  Hence we recommend that this feature should not yet be used.
  Because of this, we haven't bothered to document the
  rationale or use for user-defined equality predicates
  (though rest assured that when we do have type classes,
  this feature will indeed be useful).<p>

<li> We have introduced new syntax to allow higher-order predicate expressions
  to use DCG notation.<p>

  For details, see the "Data-terms" section of the "Syntax" chapter
  and/or the "Creating higher-order terms" section of the "Higher-order"
  chapter in the Mercury language reference manual.<p>
</ul>

<h3>Changes to the Mercury standard library</h3>

<ul>
<li> We have rewritten the `store' module to use unique modes.<p>

  The `store' module provides a declarative interface to mutable variables
  with destructive update.<p>

<li> The library predicate unsorted_aggregate/4 in std_util.m
  now interleaves calls of the aggregation predicate with
  the generation of solutions, rather than first finding all
  solutions and then aggregating them.  This allows you
  to print out solutions as they are found, for example.<p>

<li> We have added a few new predicates, namely list__takewhile/4,
  bag__to_list/2, and varset__new_named_var/4.<p>

<li> We have changed the interface to lexer__get_token_list to use a more
  efficient representation of lists of tokens. The functionality is
  unchanged.<p>

<li> We have fixed a problem where io__call_system/4 was not returning the
  the exit code of the invoked command on some operating systems.<p>

<li> We have fixed a bug in relation__rtc/4.<p>
</ul>


<h3>New library packages in the `extras' distribution</h3>

<ul>
<li> We have added a CLP(R) interface.<p>

  The new library package `cfloat_lib', in the extras/clpr directory,
  is a Mercury interface to the CLP(R) constraint solver.  The module
  `cfloat' defines a type `cfloat' for constrained floating point numbers,
  together with the usual arithmetic operators (+, -, *, /, <, >, =<, >=)
  as well as some non-linear constraint functions (abs, min, max,
  sin, cos, arcsin, and arccos).  The module `dump' provides I/O predicates
  for printing out constraints.<p>

  Note that since `cfloat' is a different type than `float', you
  have to use the `==' operator provided in this package rather
  than `=' if you want to unify a cfloat with a float.<p>
  
  We don't yet support any equivalent to SICStus Prolog's
  call_residue/3 or the three-argument version of CLP(R)'s dump
  predicate.<p>

  But apart from that, it all works nicely.  And even though we support
  equivalents to such nasty non-logical meta-programming constructs
  as CLPR's `dump' primitive, we still manage to preserve referential
  transparency -- the interface provided is a completely pure declarative
  interface.<p>

<li> We have added some support for Prolog-style variables and
  coroutining.<p>

  The module extras/trailed_updated/var.m provides a type `var(T)'
  which is a Prolog-style variable that holds a value of type T.
  These variables can have the new inst `any' described above.
  There's also an implementation of freeze/2, for coroutining
  (dynamic scheduling).  The extras/trailed_update/samples subdirectory
  has an example of the use of freeze/2 to solve the N-queens
  problem.<p>

<li> We have added library modules for backtrackable destructive update.<p>

  See the new modules `tr_array' and `tr_store' in the extras/trailed_update.
  These are versions of `array' and `store' that use trailed backtrackable
  destructive update.  The extras/trailed_update/samples subdirectory
  has an example of the use of tr_store to provide a reasonably efficient
  meta-interpreter.<p>

<li> We have added an interface to ODBC databases in extras/odbc.<p>

  Thanks to the people from Mission Critical, in particular Renaud Paquay,
  for providing the original version.<p>
</ul>

<h3>Changes to the Mercury compiler</h3>

<ul>
<li> We have added support for termination analysis.<p>

  For details, see the "Termination analysis" subsection of the
  "Implementation-dependent pragmas" section of the "Pragmas" chapter
  of the Mercury language reference manual.<p>

  This implementation is experimental, but our tests show that it is
  capable of proving the termination of most predicates and functions
  in real programs.<p>

  The current implementation of termination analysis depends on the
  third-party package lp_solve. This is package is available from
  <ftp://ftp.es.ele.tue.nl/pub/lpsolve>; it is also included in the
  lp_solve subdirectory of the Mercury source distribution. Note
  that the copyright of lp_solve includes substantial restrictions.<p>

  Details of the analysis is available in "Termination Analysis for
  Mercury" by Chris Speirs, Zoltan Somogyi and Harald Sondergaard. In P.
  Van Hentenryck, editor, "Static Analysis: Proceedings of the Fourth
  International Symposium", Lecture Notes in Computer Science. Springer,
  1997.  A longer version is available for download from
  <http://www.cs.mu.oz.au/publications/tr_db/mu_97_09.ps.gz>.<p>

<li> We have made it easier to use different compilation models ("grades").

  The Mercury compiler (mmc), the Mercury front-end to GNU C (mgnuc),
  and the Mercury linker (ml) now figure out which grade to use based
  on the options specified.  This means that for example to enable
  profiling, you can just compile and link with `--profiling', rather
  than having to specify grade `asm_fast.gc.prof'.<p>

  Attempts to mix object files compiled with different grades should now
  result in errors at link time rather than undefined behaviour.<p>

<li> We have improved the C interface.<p>

  We now handle the case when `main' is defined in C rather than in Mercury
  slightly more cleanly -- there are functions mercury_init()
  and mercury_terminate() for initializing and terminating the
  Mercury runtime.  See runtime/init.h for documentation of the functions,
  and see samples/c_interface/simpler_c_calls_mercury for an example of
  their use.<p>

<li> The compiler does a better job of constant-propagation
  optimization.<p>

<li> We have fixed a few minor bugs.<p>
</ul>
