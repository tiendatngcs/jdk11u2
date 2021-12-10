/*
 * Copyright (c) 2018, Red Hat, Inc. All rights reserved.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#include "precompiled.hpp"
#include "gc/shenandoah/shenandoahBarrierSet.inline.hpp"
#include "gc/shenandoah/shenandoahBarrierSetClone.inline.hpp"
#include "gc/shenandoah/shenandoahRuntime.hpp"
#include "gc/shenandoah/shenandoahThreadLocalData.hpp"
#include "runtime/interfaceSupport.inline.hpp"
#include "oops/oop.inline.hpp"
#include "utilities/copy.hpp"

void ShenandoahRuntime::arraycopy_barrier_oop_entry(oop* src, oop* dst, size_t length) {
  ShenandoahBarrierSet *bs = ShenandoahBarrierSet::barrier_set();
  bs->arraycopy_barrier(src, dst, length);
}

void ShenandoahRuntime::arraycopy_barrier_narrow_oop_entry(narrowOop* src, narrowOop* dst, size_t length) {
  ShenandoahBarrierSet *bs = ShenandoahBarrierSet::barrier_set();
  bs->arraycopy_barrier(src, dst, length);
}

// Shenandoah pre write barrier slowpath
JRT_LEAF(void, ShenandoahRuntime::write_ref_field_pre_entry(oopDesc* orig, JavaThread *thread))
  // tty->print_raw("ShenandoahRuntime::write_ref_field_pre_entry\n");
  orig->add_access_counter(1);
  // tty->print_cr("orgi oop: ac %lu | epoch %lu", orig->access_counter(), orig->gc_epoch());
  assert(orig != NULL, "should be optimized out");
  shenandoah_assert_correct(NULL, orig);
  // store the original value that was in the field reference
  assert(ShenandoahThreadLocalData::satb_mark_queue(thread).is_active(), "Shouldn't be here otherwise");
  ShenandoahThreadLocalData::satb_mark_queue(thread).enqueue_known_active(orig);
JRT_END

JRT_LEAF(oopDesc*, ShenandoahRuntime::load_reference_barrier(oopDesc* src, oop* load_addr))
  // tty->print_raw("ShenandoahRuntime::load_reference_barrier\n");
  src->add_access_counter(1);
  // tty->print_cr("src oop: ac %lu | epoch %lu", src->access_counter(), src->gc_epoch());
  oop load = *load_addr;
  load->add_access_counter(1);
  // tty->print_cr("load oop: ac %lu | epoch %lu", load->access_counter(), load->gc_epoch());
  return ShenandoahBarrierSet::barrier_set()->load_reference_barrier_mutator(src, load_addr);
JRT_END

JRT_LEAF(oopDesc*, ShenandoahRuntime::load_reference_barrier_narrow(oopDesc* src, narrowOop* load_addr))
  // tty->print_raw("ShenandoahRuntime::load_reference_barrier_narrow\n");
  src->add_access_counter(1);
  // tty->print_cr("src oop: ac %lu | epoch %lu", src->access_counter(), src->gc_epoch());
  oop load = CompressedOops::decode(*load_addr);
  load->add_access_counter(1);
  // tty->print_cr("load oop: ac %lu | epoch %lu", load->access_counter(), load->gc_epoch());
  return ShenandoahBarrierSet::barrier_set()->load_reference_barrier_mutator(src, load_addr);
JRT_END

// Shenandoah clone barrier: makes sure that references point to to-space
// in cloned objects.
JRT_LEAF(void, ShenandoahRuntime::shenandoah_clone_barrier(oopDesc* src))
  // tty->print_raw("ShenandoahRuntime::shenandoah_clone_barrier\n");
  oop s = oop(src);
  s->add_access_counter(1);
  // tty->print_cr("s oop: ac %lu | epoch %lu", s->access_counter(), s->gc_epoch());
  shenandoah_assert_correct(NULL, s);
  ShenandoahBarrierSet::barrier_set()->clone_barrier(s);
JRT_END
