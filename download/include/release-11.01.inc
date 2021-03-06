<h2>New in release 11.01 of the Mercury distribution</h2>

Upcoming changes to the Mercury standard library:
<p>
In the next release after 11.01 we intend to change the argument order of
many of the predicates in the standard library so as to make them more
conducive to the use of state variable notation.

<p>

For example, map.insert/4 will be changed from
<pre>      
    map.insert(map(K, V)::in, K::in, V::in, map(K, V)::out) is semidet.
</pre>
to
<pre>
    map.insert(K::in, V::in, map(K, V)::in, map(K, V)::out) is semidet.
</pre>

<p>

As part of this change, the sv* modules will be deprecated; they will
be removed from the library in a later release.

<p>

Note that none of these upcoming changes affect the 11.01 release.

<h3>HIGHLIGHTS</h3>

Changes to the Mercury language:

<ul>
<li> We have added two new kinds of scopes to the language.
<p>
  A scope introduced by one of the new keywords require_det, require_semidet,
  require_multi, require_nondet, require_cc_multi, require_cc_nondet,
  require_erroneous and require_failure, as the name implies, requires
  the goal inside the scope to have the given determinism.
<p> 
  A scope introduced by the keyword require_complete_switch requires the
  goal inside the scope, if it is a switch on the variable named by the scope,
  to be a complete switch, i.e. to have arms for all the function symbols
  in the type of the switched-on variable.
</ul>

<p>
Changes to the Mercury standard library:

<ul>
<li>We have added semidet modes for hash_table.fold/4 and
  version_hash_table.fold/4.

<li>We have added new predicates and functions to the assoc_list module.
  The predicates map_keys_only/3 map_values_only/3 and map_values/3 complement
  the functions of the same name. The predicates filter/3, negated_filter/3,
  filter/4, merge/3, which also have function versions, do jobs very similar
  to the predicates of the same name in the list module, but do the relevant
  operations on keys instead of entire list elements.

<li>We have moved the lazy evaluation module out of the extras distribution and
  into a new standard library module called `lazy'.  It has also been made
  backend-agnostic.

<li>We have made changes to the list module of the standard library:
  <ul>
  <li>We added a new predicate list.member_index0/3.  It is like list.member/2
    except that it also takes a parameter representing the zero-based index of
    the element within the list.

  <li>We added a new predicate list.map3_foldl/7 which maps over a list producing
    three lists and one folded value.
  
  <li>We added semidet modes with unique accumulators for list.foldl3/8,
    list.foldl4/10, list.foldl5/12, and list.foldl6/14.
  </ul>

<li>We have added the predicates divide/4 and divide_by_set/4 to the tree_bitset
  module of the standard library.

<li>We have added the predicates set_ctree234.member/2 and
  set_ctree234.non_empty/1.  We have add the function
  set_ctree234.from_list/1.

<li>We have added the the predicate set_bbbtree.count/2 and the
  function set_bbbtree.count/1.  These replace the predicate
  set_bbbtree.size/2 which is now deprecated.  

<li>We have added the predicate set_ordlist.non_empty/1.

<li>We have added the predicate set_tree234.non_empty/1 and the
  function set_tree234.from_list/1.

<li>We have added the predicates set_unordlist.non_empty/1 and
  set_unordlist.count/2, and the function set_unordlist.count/1. 

<li>All of the modules in the standard library that implement the set ADT,
  (set, set_ordlist, set_unordlist, set_bbbtree, set_tree234,
  and set_ctree234), now support folding over sets with up to six
  accumulators.  Modes that provide unique and mostly-unique accumulators
  for set fold have also been added.

<li>We have made the following changes to the array module of the standard
  library:

  <ul>
  <li>We have added the functions unsafe_elem/2 and append/2.

  <li>We have added the predicates svset/4, unsafe_svset/4, foldl2/4, foldl2/6,
    foldr/4, foldr2/6, map_foldl/5, map_corresponding_foldl/6, and member/2.
  </ul>

<li>We have added the predicates version_array.foldl2/6, version_array.foldr/4,
  and version_array.foldr2/6 to the standard library.

<li>We have added semidet modes with unique and mostly-unique accumulators for
  the following predicates:
	<ul>
	<li>bimap.foldl2/6
	<li>bimap.foldl3/8
	<li>cord.foldl_pred/4
  	<li>cord.map_foldl/5
	<li>list.map_corresponding_foldl2/8
	<li>list.map_corresponding_foldl3/10
	<li>list.map_corresponding3_foldl/7
	<li>map.foldl3/8
	</ul>

<li>We have added the predicate unsorted_aggregate2/6 to the solutions module
  of the standard library.

<li>We have added several predicates and functions to the require module
  of the standard library. The predicates sorry/2 and sorry/3 report
  the absence of a feature, while the predicates unexpected/2 and unexpected/3
  report an internal error in the program; all have function versions too.
  The predicate expect/3 calls unexpected if a condition isn't satisfied.
  We now have expect/4 as well as expect/3. For expect/4 as well as expect/3,
  the first and last arguments are the expected condition and the error message
  respectively, but with expect/4, there are two arguments in the middle
  to specify the location of the error (normally the name of the module
  and of the predicate respectively). We also added expect_not/3 and
  expect_not/4, which are like expect/3 and expect/4 respectively,
  except they expect the condition to be *false*, not true.
</ul>

<p>
Changes to the Mercury compiler:

<ul>
<li>We have added a new backend that generates C#.

<li>Support for building and linking against frameworks on Mac OS X has been improved.
</ul>

<p>
Changes to the extras distribution:

<ul>
<li>We have added a binding to the Cairo 2D graphics library.
</ul>


<h3>DETAILED LISTING</h3>

<p>
Changes to the Mercury compiler:

<ul>
<li>We have added a new backend that generates C#.
  For more details, see the README.CSharp.
<p>
  The new backend was contributed by
  <a href="http://www.missioncriticalit.com/">Mission Critical IT</a>.

<li>We have added two new options, `--framework' and `--framework-directory'
  in order to simplify building and linking against frameworks on Mac OS X.
  (-F is supported as a synonym for `--framework-directory'.)

<li>Switches on strings in which all output arguments in all switch arms are
  bound to constants are now implemented using lookup tables on the LLDS
  back end. This should make the generated code more compact as well as faster.
</ul>
