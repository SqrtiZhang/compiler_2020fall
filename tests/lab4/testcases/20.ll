; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/20.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define float @funa(i32 %0) {
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
  %2 = alloca i32
  store i32 10, i32* %1
  %3 = load i32, i32* %1
  %4 = call float @funa(i32 %3)
  %5 = fptosi float %4 to i32
  store i32 %5, i32* %2
  %6 = load i32, i32* %2
  ret i32 %6
}
