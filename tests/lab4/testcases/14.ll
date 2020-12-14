; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/14.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  %2 = alloca float
  store float 0x3ff99999a0000000, float* %2
  %3 = load float, float* %2
  %4 = fptosi float %3 to i32
  store i32 %4, i32* %1
  %5 = load i32, i32* %1
  ret i32 %5
}
