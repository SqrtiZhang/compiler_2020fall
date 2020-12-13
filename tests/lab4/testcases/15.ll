; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/15.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define float @funb(i32 %0) {
label.entry:
  %1 = alloca i32
  store i32 %0, i32* %1
  %2 = alloca float
  %3 = load i32, i32* %1
  %4 = sitofp i32 %3 to float
  ret float %4
}
define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  %2 = alloca float
  store i32 1, i32* %1
  %3 = load i32, i32* %1
  %4 = call float @funb(i32 %3)
  store float %4, float* %2
  %5 = load float, float* %2
  %6 = fptosi float %5 to i32
  ret i32 %6
}
