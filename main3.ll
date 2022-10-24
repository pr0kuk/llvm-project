; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.Point = type { i32, i32, i32 }

@pixels = internal global [800 x [800 x %struct.Point]] zeroinitializer, align 16
@points = internal global [10 x %struct.Point] zeroinitializer, align 16
@flag_no_recalc = internal global i32 0, align 4
@show_window = internal global i32 1, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @dist(%struct.Point* %0, %struct.Point* %1) #0 {
  %3 = alloca %struct.Point*, align 8
  %4 = alloca %struct.Point*, align 8
  store %struct.Point* %0, %struct.Point** %3, align 8
  store %struct.Point* %1, %struct.Point** %4, align 8
  %5 = load %struct.Point*, %struct.Point** %4, align 8
  %6 = getelementptr inbounds %struct.Point, %struct.Point* %5, i32 0, i32 1
  %7 = load i32, i32* %6, align 4
  %8 = load %struct.Point*, %struct.Point** %3, align 8
  %9 = getelementptr inbounds %struct.Point, %struct.Point* %8, i32 0, i32 1
  %10 = load i32, i32* %9, align 4
  %11 = sub nsw i32 %7, %10
  %12 = load %struct.Point*, %struct.Point** %4, align 8
  %13 = getelementptr inbounds %struct.Point, %struct.Point* %12, i32 0, i32 1
  %14 = load i32, i32* %13, align 4
  %15 = load %struct.Point*, %struct.Point** %3, align 8
  %16 = getelementptr inbounds %struct.Point, %struct.Point* %15, i32 0, i32 1
  %17 = load i32, i32* %16, align 4
  %18 = sub nsw i32 %14, %17
  %19 = mul nsw i32 %11, %18
  %20 = load %struct.Point*, %struct.Point** %4, align 8
  %21 = getelementptr inbounds %struct.Point, %struct.Point* %20, i32 0, i32 2
  %22 = load i32, i32* %21, align 4
  %23 = load %struct.Point*, %struct.Point** %3, align 8
  %24 = getelementptr inbounds %struct.Point, %struct.Point* %23, i32 0, i32 2
  %25 = load i32, i32* %24, align 4
  %26 = sub nsw i32 %22, %25
  %27 = load %struct.Point*, %struct.Point** %4, align 8
  %28 = getelementptr inbounds %struct.Point, %struct.Point* %27, i32 0, i32 2
  %29 = load i32, i32* %28, align 4
  %30 = load %struct.Point*, %struct.Point** %3, align 8
  %31 = getelementptr inbounds %struct.Point, %struct.Point* %30, i32 0, i32 2
  %32 = load i32, i32* %31, align 4
  %33 = sub nsw i32 %29, %32
  %34 = mul nsw i32 %26, %33
  %35 = add nsw i32 %19, %34
  ret i32 %35
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @calc_new_centers() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca [10 x i32], align 16
  %4 = alloca [10 x i32], align 16
  %5 = alloca [10 x i32], align 16
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 0, i32* %2, align 4
  store i32 0, i32* %6, align 4
  br label %10

10:                                               ; preds = %23, %0
  %11 = load i32, i32* %6, align 4
  %12 = icmp slt i32 %11, 10
  br i1 %12, label %13, label %26

13:                                               ; preds = %10
  %14 = load i32, i32* %6, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %15
  store i32 0, i32* %16, align 4
  %17 = load i32, i32* %6, align 4
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %18
  store i32 0, i32* %19, align 4
  %20 = load i32, i32* %6, align 4
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds [10 x i32], [10 x i32]* %5, i64 0, i64 %21
  store i32 0, i32* %22, align 4
  br label %23

23:                                               ; preds = %13
  %24 = load i32, i32* %6, align 4
  %25 = add nsw i32 %24, 1
  store i32 %25, i32* %6, align 4
  br label %10

26:                                               ; preds = %10
  store i32 0, i32* %7, align 4
  br label %27

27:                                               ; preds = %102, %26
  %28 = load i32, i32* %7, align 4
  %29 = icmp slt i32 %28, 800
  br i1 %29, label %30, label %105

30:                                               ; preds = %27
  store i32 0, i32* %8, align 4
  br label %31

31:                                               ; preds = %98, %30
  %32 = load i32, i32* %8, align 4
  %33 = icmp slt i32 %32, 800
  br i1 %33, label %34, label %101

34:                                               ; preds = %31
  %35 = load i32, i32* %7, align 4
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %36
  %38 = load i32, i32* %8, align 4
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %37, i64 0, i64 %39
  %41 = getelementptr inbounds %struct.Point, %struct.Point* %40, i32 0, i32 0
  %42 = load i32, i32* %41, align 4
  %43 = icmp sge i32 %42, 0
  br i1 %43, label %44, label %97

44:                                               ; preds = %34
  %45 = load i32, i32* %7, align 4
  %46 = sext i32 %45 to i64
  %47 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %46
  %48 = load i32, i32* %8, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %47, i64 0, i64 %49
  %51 = getelementptr inbounds %struct.Point, %struct.Point* %50, i32 0, i32 1
  %52 = load i32, i32* %51, align 4
  %53 = load i32, i32* %7, align 4
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %54
  %56 = load i32, i32* %8, align 4
  %57 = sext i32 %56 to i64
  %58 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %55, i64 0, i64 %57
  %59 = getelementptr inbounds %struct.Point, %struct.Point* %58, i32 0, i32 0
  %60 = load i32, i32* %59, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %61
  %63 = load i32, i32* %62, align 4
  %64 = add nsw i32 %63, %52
  store i32 %64, i32* %62, align 4
  %65 = load i32, i32* %7, align 4
  %66 = sext i32 %65 to i64
  %67 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %66
  %68 = load i32, i32* %8, align 4
  %69 = sext i32 %68 to i64
  %70 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %67, i64 0, i64 %69
  %71 = getelementptr inbounds %struct.Point, %struct.Point* %70, i32 0, i32 2
  %72 = load i32, i32* %71, align 4
  %73 = load i32, i32* %7, align 4
  %74 = sext i32 %73 to i64
  %75 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %74
  %76 = load i32, i32* %8, align 4
  %77 = sext i32 %76 to i64
  %78 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %75, i64 0, i64 %77
  %79 = getelementptr inbounds %struct.Point, %struct.Point* %78, i32 0, i32 0
  %80 = load i32, i32* %79, align 4
  %81 = sext i32 %80 to i64
  %82 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %81
  %83 = load i32, i32* %82, align 4
  %84 = add nsw i32 %83, %72
  store i32 %84, i32* %82, align 4
  %85 = load i32, i32* %7, align 4
  %86 = sext i32 %85 to i64
  %87 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %86
  %88 = load i32, i32* %8, align 4
  %89 = sext i32 %88 to i64
  %90 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %87, i64 0, i64 %89
  %91 = getelementptr inbounds %struct.Point, %struct.Point* %90, i32 0, i32 0
  %92 = load i32, i32* %91, align 4
  %93 = sext i32 %92 to i64
  %94 = getelementptr inbounds [10 x i32], [10 x i32]* %5, i64 0, i64 %93
  %95 = load i32, i32* %94, align 4
  %96 = add nsw i32 %95, 1
  store i32 %96, i32* %94, align 4
  br label %97

97:                                               ; preds = %44, %34
  br label %98

98:                                               ; preds = %97
  %99 = load i32, i32* %8, align 4
  %100 = add nsw i32 %99, 1
  store i32 %100, i32* %8, align 4
  br label %31

101:                                              ; preds = %31
  br label %102

102:                                              ; preds = %101
  %103 = load i32, i32* %7, align 4
  %104 = add nsw i32 %103, 1
  store i32 %104, i32* %7, align 4
  br label %27

105:                                              ; preds = %27
  store i32 0, i32* %9, align 4
  br label %106

106:                                              ; preds = %162, %105
  %107 = load i32, i32* %9, align 4
  %108 = icmp slt i32 %107, 10
  br i1 %108, label %109, label %165

109:                                              ; preds = %106
  %110 = load i32, i32* %9, align 4
  %111 = sext i32 %110 to i64
  %112 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %111
  %113 = load i32, i32* %112, align 4
  %114 = load i32, i32* %9, align 4
  %115 = sext i32 %114 to i64
  %116 = getelementptr inbounds [10 x i32], [10 x i32]* %5, i64 0, i64 %115
  %117 = load i32, i32* %116, align 4
  %118 = sdiv i32 %113, %117
  store i32 %118, i32* %2, align 4
  %119 = load i32, i32* %9, align 4
  %120 = sext i32 %119 to i64
  %121 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %120
  %122 = getelementptr inbounds %struct.Point, %struct.Point* %121, i32 0, i32 1
  %123 = load i32, i32* %122, align 4
  %124 = load i32, i32* %2, align 4
  %125 = icmp eq i32 %123, %124
  br i1 %125, label %126, label %129

126:                                              ; preds = %109
  %127 = load i32, i32* %1, align 4
  %128 = add nsw i32 %127, 1
  store i32 %128, i32* %1, align 4
  br label %135

129:                                              ; preds = %109
  %130 = load i32, i32* %2, align 4
  %131 = load i32, i32* %9, align 4
  %132 = sext i32 %131 to i64
  %133 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %132
  %134 = getelementptr inbounds %struct.Point, %struct.Point* %133, i32 0, i32 1
  store i32 %130, i32* %134, align 4
  br label %135

135:                                              ; preds = %129, %126
  %136 = load i32, i32* %9, align 4
  %137 = sext i32 %136 to i64
  %138 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %137
  %139 = load i32, i32* %138, align 4
  %140 = load i32, i32* %9, align 4
  %141 = sext i32 %140 to i64
  %142 = getelementptr inbounds [10 x i32], [10 x i32]* %5, i64 0, i64 %141
  %143 = load i32, i32* %142, align 4
  %144 = sdiv i32 %139, %143
  store i32 %144, i32* %2, align 4
  %145 = load i32, i32* %9, align 4
  %146 = sext i32 %145 to i64
  %147 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %146
  %148 = getelementptr inbounds %struct.Point, %struct.Point* %147, i32 0, i32 2
  %149 = load i32, i32* %148, align 4
  %150 = load i32, i32* %2, align 4
  %151 = icmp eq i32 %149, %150
  br i1 %151, label %152, label %155

152:                                              ; preds = %135
  %153 = load i32, i32* %1, align 4
  %154 = add nsw i32 %153, 1
  store i32 %154, i32* %1, align 4
  br label %161

155:                                              ; preds = %135
  %156 = load i32, i32* %2, align 4
  %157 = load i32, i32* %9, align 4
  %158 = sext i32 %157 to i64
  %159 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %158
  %160 = getelementptr inbounds %struct.Point, %struct.Point* %159, i32 0, i32 2
  store i32 %156, i32* %160, align 4
  br label %161

161:                                              ; preds = %155, %152
  br label %162

162:                                              ; preds = %161
  %163 = load i32, i32* %9, align 4
  %164 = add nsw i32 %163, 1
  store i32 %164, i32* %9, align 4
  br label %106

165:                                              ; preds = %106
  %166 = load i32, i32* %1, align 4
  ret i32 %166
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @calc_vor_diag() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  br label %6

6:                                                ; preds = %70, %0
  %7 = load i32, i32* %1, align 4
  %8 = icmp slt i32 %7, 800
  br i1 %8, label %9, label %73

9:                                                ; preds = %6
  store i32 0, i32* %2, align 4
  store i32 1000000000, i32* %3, align 4
  br label %10

10:                                               ; preds = %50, %9
  %11 = load i32, i32* %2, align 4
  %12 = icmp slt i32 %11, 800
  br i1 %12, label %13, label %69

13:                                               ; preds = %10
  store i32 0, i32* %4, align 4
  store i32 0, i32* %5, align 4
  br label %14

14:                                               ; preds = %46, %13
  %15 = load i32, i32* %4, align 4
  %16 = icmp slt i32 %15, 10
  br i1 %16, label %17, label %20

17:                                               ; preds = %14
  %18 = load i32, i32* %3, align 4
  %19 = icmp sgt i32 %18, 0
  br label %20

20:                                               ; preds = %17, %14
  %21 = phi i1 [ false, %14 ], [ %19, %17 ]
  br i1 %21, label %22, label %49

22:                                               ; preds = %20
  %23 = load i32, i32* %1, align 4
  %24 = sext i32 %23 to i64
  %25 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %24
  %26 = load i32, i32* %2, align 4
  %27 = sext i32 %26 to i64
  %28 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %25, i64 0, i64 %27
  %29 = load i32, i32* %4, align 4
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %30
  %32 = call i32 @dist(%struct.Point* %28, %struct.Point* %31)
  store i32 %32, i32* %5, align 4
  %33 = load i32, i32* %3, align 4
  %34 = icmp slt i32 %32, %33
  br i1 %34, label %35, label %45

35:                                               ; preds = %22
  %36 = load i32, i32* %5, align 4
  store i32 %36, i32* %3, align 4
  %37 = load i32, i32* %4, align 4
  %38 = load i32, i32* %1, align 4
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %39
  %41 = load i32, i32* %2, align 4
  %42 = sext i32 %41 to i64
  %43 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %40, i64 0, i64 %42
  %44 = getelementptr inbounds %struct.Point, %struct.Point* %43, i32 0, i32 0
  store i32 %37, i32* %44, align 4
  br label %45

45:                                               ; preds = %35, %22
  br label %46

46:                                               ; preds = %45
  %47 = load i32, i32* %4, align 4
  %48 = add nsw i32 %47, 1
  store i32 %48, i32* %4, align 4
  br label %14

49:                                               ; preds = %20
  br label %50

50:                                               ; preds = %49
  %51 = load i32, i32* %2, align 4
  %52 = load i32, i32* %1, align 4
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %53
  %55 = load i32, i32* %2, align 4
  %56 = sext i32 %55 to i64
  %57 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %54, i64 0, i64 %56
  %58 = getelementptr inbounds %struct.Point, %struct.Point* %57, i32 0, i32 1
  store i32 %51, i32* %58, align 4
  %59 = load i32, i32* %1, align 4
  %60 = load i32, i32* %1, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %61
  %63 = load i32, i32* %2, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %62, i64 0, i64 %64
  %66 = getelementptr inbounds %struct.Point, %struct.Point* %65, i32 0, i32 2
  store i32 %59, i32* %66, align 4
  %67 = load i32, i32* %2, align 4
  %68 = add nsw i32 %67, 1
  store i32 %68, i32* %2, align 4
  store i32 1000000000, i32* %3, align 4
  br label %10

69:                                               ; preds = %10
  br label %70

70:                                               ; preds = %69
  %71 = load i32, i32* %1, align 4
  %72 = add nsw i32 %71, 1
  store i32 %72, i32* %1, align 4
  br label %6

73:                                               ; preds = %6
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @display() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  call void @calc_vor_diag()
  call void (...) @gl_start()
  store i32 0, i32* %1, align 4
  br label %3

3:                                                ; preds = %21, %0
  %4 = load i32, i32* %1, align 4
  %5 = icmp slt i32 %4, 800
  br i1 %5, label %6, label %24

6:                                                ; preds = %3
  store i32 0, i32* %2, align 4
  br label %7

7:                                                ; preds = %17, %6
  %8 = load i32, i32* %2, align 4
  %9 = icmp slt i32 %8, 800
  br i1 %9, label %10, label %20

10:                                               ; preds = %7
  %11 = load i32, i32* %1, align 4
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %12
  %14 = load i32, i32* %2, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %13, i64 0, i64 %15
  call void @gl_put_pixel(%struct.Point* %16)
  br label %17

17:                                               ; preds = %10
  %18 = load i32, i32* %2, align 4
  %19 = add nsw i32 %18, 1
  store i32 %19, i32* %2, align 4
  br label %7

20:                                               ; preds = %7
  br label %21

21:                                               ; preds = %20
  %22 = load i32, i32* %1, align 4
  %23 = add nsw i32 %22, 1
  store i32 %23, i32* %1, align 4
  br label %3

24:                                               ; preds = %3
  call void (...) @gl_flush()
  ret void
}

declare dso_local void @gl_start(...) #1

declare dso_local void @gl_put_pixel(%struct.Point*) #1

declare dso_local void @gl_flush(...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @timf(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* @flag_no_recalc, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %5, label %11

5:                                                ; preds = %1
  %6 = call i32 @calc_new_centers()
  %7 = icmp slt i32 %6, 20
  br i1 %7, label %8, label %9

8:                                                ; preds = %5
  call void @display()
  br label %10

9:                                                ; preds = %5
  store i32 1, i32* @flag_no_recalc, align 4
  br label %10

10:                                               ; preds = %9, %8
  br label %11

11:                                               ; preds = %10, %1
  %12 = load i32, i32* %2, align 4
  call void @set_timer(i32 %12)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @set_timer(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @reset_picture() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  br label %2

2:                                                ; preds = %18, %0
  %3 = load i32, i32* %1, align 4
  %4 = icmp slt i32 %3, 10
  br i1 %4, label %5, label %21

5:                                                ; preds = %2
  %6 = call i32 (...) @int_rand()
  %7 = srem i32 %6, 800
  %8 = load i32, i32* %1, align 4
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %9
  %11 = getelementptr inbounds %struct.Point, %struct.Point* %10, i32 0, i32 1
  store i32 %7, i32* %11, align 4
  %12 = call i32 (...) @int_rand()
  %13 = srem i32 %12, 800
  %14 = load i32, i32* %1, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %15
  %17 = getelementptr inbounds %struct.Point, %struct.Point* %16, i32 0, i32 2
  store i32 %13, i32* %17, align 4
  br label %18

18:                                               ; preds = %5
  %19 = load i32, i32* %1, align 4
  %20 = add nsw i32 %19, 1
  store i32 %20, i32* %1, align 4
  br label %2

21:                                               ; preds = %2
  call void @calc_vor_diag()
  store i32 0, i32* @flag_no_recalc, align 4
  ret void
}

declare dso_local i32 @int_rand(...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @loop() #0 {
  call void @display()
  br label %1

1:                                                ; preds = %4, %0
  %2 = load i32, i32* @show_window, align 4
  %3 = icmp eq i32 %2, 1
  br i1 %3, label %4, label %5

4:                                                ; preds = %1
  call void @timf(i32 10)
  br label %1

5:                                                ; preds = %1
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @exit_loop() #0 {
  store i32 0, i32* @show_window, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 %0, i8** %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  %6 = load i32, i32* %4, align 4
  %7 = load i8**, i8*** %5, align 8
  call void @gl_init(i32 %6, i8** %7)
  call void @reset_picture()
  call void @loop()
  ret i32 0
}

declare dso_local void @gl_init(i32, i8**) #1

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0-4ubuntu1 "}
