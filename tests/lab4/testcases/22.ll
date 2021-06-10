; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/22.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  %2 = alloca i32
  %3 = alloca i32
  %4 = alloca i32
  %5 = alloca i32
  store i32 5, i32* %3
  store i32 9, i32* %4
  %6 = load i32, i32* %3
  %7 = load i32, i32* %4
  %8 = add i32 %6, %7
  store i32 %8, i32* %2
  store i32 %8, i32* %1
  store i32 %8, i32* %5
  %9 = load i32, i32* %5
  ret i32 %9
}
