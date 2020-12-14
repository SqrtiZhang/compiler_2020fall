; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/23.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @testa(i32* %0) {
label.entry:
  %1 = alloca i32*
  store i32* %0, i32** %1
  %2 = alloca i32
  %3 = load i32*, i32** %1
  %4 = getelementptr i32, i32* %3, i32 0
  %5 = load i32, i32* %4
  ret i32 %5
}
define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca [10 x i32]
  %2 = getelementptr [10 x i32], [10 x i32]* %1, i32 0, i32 0
  store i32 1, i32* %2
  %3 = getelementptr [10 x i32], [10 x i32]* %1, i32 0, i32 1
  %4 = getelementptr [10 x i32], [10 x i32]* %1, i32 0, i32 0
  %5 = call i32 @testa(i32* %4)
  store i32 %5, i32* %3
  %6 = getelementptr [10 x i32], [10 x i32]* %1, i32 0, i32 1
  %7 = load i32, i32* %6
  ret i32 %7
}
