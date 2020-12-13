; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/13.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @gcd(i32 %0, i32 %1) {
label.entry:
  %2 = alloca i32
  store i32 %0, i32* %2
  %3 = alloca i32
  store i32 %1, i32* %3
  %4 = alloca i32
  %5 = load i32, i32* %3
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %label.trueBB, label %label.falseBB
label.trueBB:
  %7 = load i32, i32* %2
  ret i32 %7
label.falseBB:
  ret i32 0
}
define void @main() {
label.entry:
  ret void
}
