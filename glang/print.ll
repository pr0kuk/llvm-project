@.str = private unnamed_addr constant [10 x i8] c"print %d\0A\00", align 1
declare dso_local i32 @printf(i8*, ...) #1
; Function Attrs: noinline optnone uwtable
define dso_local void @print(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0), i32 %3)
  ret void
}
