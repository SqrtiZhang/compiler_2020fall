; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/13.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca [2 x i32]
  %2 = alloca i32
  store i32 1, i32* %2
  %3 = load i32, i32* %2
  %4 = getelementptr [2 x i32], [2 x i32]* %1, i32 0, i32 %3
  %5 = load i32, i32* %2
  store i32 %5, i32* %4
  %6 = getelementptr [2 x i32], [2 x i32]* %1, i32 0, i32 1
  %7 = load i32, i32* %6
  ret i32 %7
}
