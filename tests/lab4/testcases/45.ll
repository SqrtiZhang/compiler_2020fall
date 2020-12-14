; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/45.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define void @foo(i32* %0) {
label.entry:
  %1 = alloca i32*
  store i32* %0, i32** %1
  %2 = alloca i32
  %3 = alloca i32
  store i32 9, i32* %3
  %4 = load i32, i32* %3
  %5 = sub i32 0, %4
  store i32 %5, i32* %3
  %6 = load i32, i32* %3
  %7 = load i32*, i32** %1
  %8 = icmp slt i32 %6, 0
  br i1 %8, label %label.negBB, label %label.afternegBB1
label.negBB:
  call void @neg_idx_except()
  ret void
label.afternegBB1:
  %9 = getelementptr i32, i32* %7, i32 %6
  %10 = load i32, i32* %9
  store i32 %10, i32* %2
  ret void
}
define void @main() {
label.entry:
  %0 = alloca [10 x i32]
  %1 = alloca i32
  store i32 2, i32* %1
  %2 = load i32, i32* %1
  %3 = sub i32 0, %2
  store i32 %3, i32* %1
  %4 = load i32, i32* %1
  %5 = icmp slt i32 %4, 0
  br i1 %5, label %label.negBB, label %label.afternegBB1
label.negBB:
  call void @neg_idx_except()
  ret void
label.afternegBB1:
  %6 = getelementptr [10 x i32], [10 x i32]* %0, i32 0, i32 %4
  %7 = load i32, i32* %6
  store i32 %7, i32* %1
  %8 = getelementptr [10 x i32], [10 x i32]* %0, i32 0, i32 0
  call void @foo(i32* %8)
  ret void
}
