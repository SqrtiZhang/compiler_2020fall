; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/32.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  store i32 10, i32* %1
  br label %label.cmp_bb1
label.cmp_bb1:
  %2 = load i32, i32* %1
  %3 = icmp slt i32 %2, 0
  br i1 %3, label %label.while_body_bb1, label %label.end_bb1
label.while_body_bb1:
  br label %label.cmp_bb1
label.end_bb1:
  br label %label.cmp_bb2
label.cmp_bb2:
  %4 = load i32, i32* %1
  %5 = sub i32 0, 1
  %6 = add i32 %5, 2
  %7 = mul i32 3, 1
  %8 = sub i32 %6, %7
  %9 = icmp slt i32 %4, %8
  br i1 %9, label %label.while_body_bb2, label %label.end_bb2
label.while_body_bb2:
  br label %label.cmp_bb2
label.end_bb2:
  %10 = load i32, i32* %1
  %11 = icmp sgt i32 %10, 0
  br i1 %11, label %label.trueBB1, label %label.falseBB1
label.trueBB1:
  br label %label.retBB1
label.falseBB1:
  %12 = load i32, i32* %1
  %13 = icmp sgt i32 %12, 1
  br i1 %13, label %label.trueBB2, label %label.retBB2
label.retBB1:
  %14 = load i32, i32* %1
  ret i32 %14
label.trueBB2:
  store i32 1, i32* %1
  br label %label.retBB2
label.falseBB2:
  br label %label.retBB2
label.retBB2:
  br label %label.retBB1
}
