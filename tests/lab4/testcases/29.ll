; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/29.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  %2 = alloca i32
  store i32 8, i32* %1
  br label %label.cmp_bb1
label.cmp_bb1:
  %3 = load i32, i32* %1
  %4 = icmp sgt i32 %3, 10
  br i1 %4, label %label.while_body_bb1, label %label.end_bb1
label.while_body_bb1:
  %5 = alloca i32
  store i32 9, i32* %2
  ret i32 0
label.end_bb1:
  %6 = load i32, i32* %1
  %7 = icmp slt i32 %6, 2
  br i1 %7, label %label.trueBB1, label %label.retBB1
label.trueBB1:
  ret i32 2
label.retBB1:
  %8 = load i32, i32* %1
  ret i32 %8
}
