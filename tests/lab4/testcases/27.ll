; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/27.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  %2 = fcmp une float 0x405ec00000000000,0x0
  br i1 %2, label %label.trueBB1, label %label.retBB1
label.trueBB1:
  store i32 1, i32* %1
  br label %label.retBB1
label.retBB1:
  %3 = load i32, i32* %1
  ret i32 %3
}
