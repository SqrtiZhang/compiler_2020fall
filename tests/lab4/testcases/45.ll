; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/45.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  store i32 1, i32* %1
  br label %label.cmp_bb1
label.cmp_bb1:
  %2 = load i32, i32* %1
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %label.while_body_bb1, label %label.end_bb1
label.while_body_bb1:
  %4 = load i32, i32* %1
  ret i32 %4
label.end_bb1:
  %5 = load i32, i32* %0
  ret i32 %5
}
