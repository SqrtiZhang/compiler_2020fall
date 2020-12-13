; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/14.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca float
  %2 = alloca i32
  store i32 1, i32* %2
  %3 = load i32, i32* %2
  store float 0x0, float* %1
  %4 = load i32, i32* %2
  ret i32 %4
}
