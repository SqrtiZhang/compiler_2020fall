; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/15.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca float
  %2 = alloca i32
  %3 = alloca i32
  store i32 1, i32* %2
  %4 = load i32, i32* %2
  store float 0x0, float* %1
  %5 = load float, float* %1
  store i32 0, i32* %3
  %6 = load i32, i32* %3
  ret i32 %6
}
