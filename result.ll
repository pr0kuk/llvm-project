; ModuleID = 'top'
source_filename = "top"

@pixels = internal global [800 x [800 x { i32, i32, i32 }]] zeroinitializer
@points = internal global [10 x { i32, i32, i32 }] zeroinitializer
@flag_no_recalc = internal global i32 0
@show_window = internal global i32 0

define i32 @main(i32 %0, i8** %1) {
entrypoint:
  %2 = alloca i32
  %3 = alloca i32
  %4 = alloca i8**
  store i32 0, i32* %2
  store i32 %0, i32* %3
  store i8** %1, i8*** %4
  %5 = load i32, i32* %3
  %6 = load i8**, i8*** %4
  call void @gl_init(i32 %5, i8** %6)
  call void @reset_picture()
  call void @loop()
  ret i32 0
}

define void @reset_picture() {
entrypoint:
  %0 = alloca i32
  store i32 0, i32* %0
  br label %"2"

"2":                                              ; preds = %"18", %entrypoint
  %1 = load i32, i32* %0
  %2 = icmp slt i32 %1, 10
  br i1 %2, label %"5", label %"21"

"5":                                              ; preds = %"2"
  %3 = call i32 @int_rand()
  %4 = srem i32 %3, 800
  %5 = load i32, i32* %0
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds [10 x { i32, i32, i32 }], [10 x { i32, i32, i32 }]* @points, i64 0, i64 %6
  %8 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %7, i32 0, i32 1
  store i32 %4, i32* %8
  %9 = call i32 @int_rand()
  %10 = srem i32 %9, 800
  %11 = load i32, i32* %0
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds [10 x { i32, i32, i32 }], [10 x { i32, i32, i32 }]* @points, i64 0, i64 %12
  %14 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %13, i32 0, i32 2
  store i32 %10, i32* %14
  br label %"18"

"18":                                             ; preds = %"5"
  %15 = load i32, i32* %0
  %16 = add nsw i32 %15, 1
  store i32 %16, i32* %0
  br label %"2"

"21":                                             ; preds = %"2"
  call void @calc_vor_diag()
  store i32 0, i32* @flag_no_recalc
  ret void
}

declare void @gl_init(i32, i8**)

define void @display() {
entrypoint:
  %0 = alloca i32
  %1 = alloca i32
  call void @calc_vor_diag()
  call void @gl_start()
  store i32 0, i32* %0
  br label %"3"

"3":                                              ; preds = %"21", %entrypoint
  %2 = load i32, i32* %0
  %3 = icmp slt i32 %2, 800
  br i1 %3, label %"6", label %"24"

"6":                                              ; preds = %"3"
  store i32 0, i32* %1
  br label %"7"

"7":                                              ; preds = %"17", %"6"
  %4 = load i32, i32* %1
  %5 = icmp slt i32 %4, 800
  br i1 %5, label %"10", label %"20"

"10":                                             ; preds = %"7"
  %6 = load i32, i32* %0
  %7 = sext i32 %6 to i64
  %8 = getelementptr inbounds [800 x [800 x { i32, i32, i32 }]], [800 x [800 x { i32, i32, i32 }]]* @pixels, i64 0, i64 %7
  %9 = load i32, i32* %1
  %10 = sext i32 %9 to i64
  %11 = getelementptr inbounds [800 x { i32, i32, i32 }], [800 x { i32, i32, i32 }]* %8, i32 0, i64 %10
  call void @gl_put_pixel({ i32, i32, i32 }* %11)
  br label %"17"

"17":                                             ; preds = %"10"
  %12 = load i32, i32* %1
  %13 = add nsw i32 %12, 1
  store i32 %13, i32* %1
  br label %"7"

"20":                                             ; preds = %"7"
  br label %"21"

"21":                                             ; preds = %"20"
  %14 = load i32, i32* %0
  %15 = add nsw i32 %14, 1
  store i32 %15, i32* %0
  br label %"3"

"24":                                             ; preds = %"3"
  call void @gl_flush()
  ret void
}

define void @timf(i32 %0) {
entrypoint:
  %1 = alloca i32
  store i32 %0, i32* %1
  %2 = load i32, i32* @flag_no_recalc
  %3 = icmp eq i32 %2, 0
  br i1 %3, label %"5", label %"11"

"5":                                              ; preds = %entrypoint
  %4 = call i32 @calc_new_centers()
  %5 = icmp slt i32 %4, 20
  br i1 %5, label %"8", label %"9"

"8":                                              ; preds = %"5"
  call void @display()
  br label %"10"

"9":                                              ; preds = %"5"
  store i32 1, i32* @flag_no_recalc
  br label %"10"

"10":                                             ; preds = %"9", %"8"
  br label %"11"

"11":                                             ; preds = %"10", %entrypoint
  %6 = load i32, i32* %1
  call void @set_timer(i32 %6)
  ret void
}

define void @loop() {
entrypoint:
  call void @display()
  br label %"1"

"1":                                              ; preds = %"4", %entrypoint
  %0 = load i32, i32* @show_window
  %1 = icmp slt i32 %0, 1
  br i1 %1, label %"4", label %"5"

"4":                                              ; preds = %"1"
  call void @timf(i32 10)
  br label %"1"

"5":                                              ; preds = %"1"
  ret void
}

declare i32 @int_rand()

define void @calc_vor_diag() {
entrypoint:
  %0 = alloca i32
  %1 = alloca i32
  %2 = alloca i32
  %3 = alloca i32
  %4 = alloca i32
  store i32 0, i32* %0
  br label %"6"

"6":                                              ; preds = %"70", %entrypoint
  %5 = load i32, i32* %0
  %6 = icmp slt i32 %5, 800
  br i1 %6, label %"9", label %"73"

"9":                                              ; preds = %"6"
  store i32 0, i32* %1
  store i32 1000000000, i32* %2
  br label %"10"

"10":                                             ; preds = %"50", %"9"
  %7 = load i32, i32* %1
  %8 = icmp slt i32 %7, 800
  br i1 %8, label %"13", label %"69"

"13":                                             ; preds = %"10"
  store i32 0, i32* %3
  store i32 0, i32* %4
  br label %"14"

"14":                                             ; preds = %"46", %"13"
  %9 = load i32, i32* %3
  %10 = icmp slt i32 %9, 10
  br i1 %10, label %"17", label %"20"

"17":                                             ; preds = %"14"
  %11 = load i32, i32* %2
  %12 = icmp sgt i32 %11, 0
  br label %"20"

"20":                                             ; preds = %"17", %"14"
  %13 = phi i1 [ false, %"14" ], [ %12, %"17" ]
  br i1 %13, label %"22", label %"49"

"22":                                             ; preds = %"20"
  %14 = load i32, i32* %0
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [800 x [800 x { i32, i32, i32 }]], [800 x [800 x { i32, i32, i32 }]]* @pixels, i64 0, i64 %15
  %17 = load i32, i32* %1
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds [800 x { i32, i32, i32 }], [800 x { i32, i32, i32 }]* %16, i32 0, i64 %18
  %20 = load i32, i32* %3
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds [10 x { i32, i32, i32 }], [10 x { i32, i32, i32 }]* @points, i64 0, i64 %21
  %23 = call i32 @dist({ i32, i32, i32 }* %19, { i32, i32, i32 }* %22)
  store i32 %23, i32* %4
  %24 = load i32, i32* %2
  %25 = icmp slt i32 %23, %24
  br i1 %25, label %"35", label %"45"

"35":                                             ; preds = %"22"
  %26 = load i32, i32* %4
  store i32 %26, i32* %2
  %27 = load i32, i32* %3
  %28 = load i32, i32* %0
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds [800 x [800 x { i32, i32, i32 }]], [800 x [800 x { i32, i32, i32 }]]* @pixels, i64 0, i64 %29
  %31 = load i32, i32* %1
  %32 = sext i32 %31 to i64
  %33 = getelementptr inbounds [800 x { i32, i32, i32 }], [800 x { i32, i32, i32 }]* %30, i32 0, i64 %32
  %34 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %33, i32 0, i32 0
  store i32 %27, i32* %34
  br label %"45"

"45":                                             ; preds = %"35", %"22"
  br label %"46"

"46":                                             ; preds = %"45"
  %35 = load i32, i32* %3
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %3
  br label %"14"

"49":                                             ; preds = %"20"
  br label %"50"

"50":                                             ; preds = %"49"
  %37 = load i32, i32* %1
  %38 = load i32, i32* %0
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds [800 x [800 x { i32, i32, i32 }]], [800 x [800 x { i32, i32, i32 }]]* @pixels, i64 0, i64 %39
  %41 = load i32, i32* %1
  %42 = sext i32 %41 to i64
  %43 = getelementptr inbounds [800 x { i32, i32, i32 }], [800 x { i32, i32, i32 }]* %40, i32 0, i64 %42
  %44 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %43, i32 0, i32 1
  store i32 %37, i32* %44
  %45 = load i32, i32* %0
  %46 = load i32, i32* %0
  %47 = sext i32 %46 to i64
  %48 = getelementptr inbounds [800 x [800 x { i32, i32, i32 }]], [800 x [800 x { i32, i32, i32 }]]* @pixels, i64 0, i64 %47
  %49 = load i32, i32* %1
  %50 = sext i32 %49 to i64
  %51 = getelementptr inbounds [800 x { i32, i32, i32 }], [800 x { i32, i32, i32 }]* %48, i32 0, i64 %50
  %52 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %51, i32 0, i32 2
  store i32 %45, i32* %52
  %53 = load i32, i32* %1
  %54 = add nsw i32 %53, 1
  store i32 %54, i32* %1
  store i32 1000000000, i32* %2
  br label %"10"

"69":                                             ; preds = %"10"
  br label %"70"

"70":                                             ; preds = %"69"
  %55 = load i32, i32* %0
  %56 = add nsw i32 %55, 1
  store i32 %56, i32* %0
  br label %"6"

"73":                                             ; preds = %"6"
  ret void
}

define i32 @dist({ i32, i32, i32 }* %0, { i32, i32, i32 }* %1) {
entrypoint:
  %2 = alloca { i32, i32, i32 }*
  %3 = alloca { i32, i32, i32 }*
  store { i32, i32, i32 }* %0, { i32, i32, i32 }** %2
  store { i32, i32, i32 }* %1, { i32, i32, i32 }** %3
  %4 = load { i32, i32, i32 }*, { i32, i32, i32 }** %3
  %5 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %4, i32 0, i32 1
  %6 = load i32, i32* %5
  %7 = load { i32, i32, i32 }*, { i32, i32, i32 }** %2
  %8 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %7, i32 0, i32 1
  %9 = load i32, i32* %8
  %10 = sub nsw i32 %6, %9
  %11 = load { i32, i32, i32 }*, { i32, i32, i32 }** %3
  %12 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %11, i32 0, i32 1
  %13 = load i32, i32* %12
  %14 = load { i32, i32, i32 }*, { i32, i32, i32 }** %2
  %15 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %14, i32 0, i32 1
  %16 = load i32, i32* %15
  %17 = sub nsw i32 %13, %16
  %18 = mul nsw i32 %10, %17
  %19 = load { i32, i32, i32 }*, { i32, i32, i32 }** %3
  %20 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %19, i32 0, i32 2
  %21 = load i32, i32* %20
  %22 = load { i32, i32, i32 }*, { i32, i32, i32 }** %2
  %23 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %22, i32 0, i32 2
  %24 = load i32, i32* %23
  %25 = sub nsw i32 %21, %24
  %26 = load { i32, i32, i32 }*, { i32, i32, i32 }** %3
  %27 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %26, i32 0, i32 2
  %28 = load i32, i32* %27
  %29 = load { i32, i32, i32 }*, { i32, i32, i32 }** %2
  %30 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %29, i32 0, i32 2
  %31 = load i32, i32* %30
  %32 = sub nsw i32 %28, %31
  %33 = mul nsw i32 %25, %32
  %34 = add nsw i32 %18, %33
  ret i32 %34
}

define void @set_timer(i32 %0) {
entrypoint:
  %1 = alloca i32
  store i32 %0, i32* %1
  ret void
}

define i32 @calc_new_centers() {
entrypoint:
  %0 = alloca i32
  %1 = alloca i32
  %2 = alloca [10 x i32]
  %3 = alloca [10 x i32]
  %4 = alloca [10 x i32]
  %5 = alloca i32
  %6 = alloca i32
  %7 = alloca i32
  %8 = alloca i32
  store i32 0, i32* %0
  store i32 0, i32* %1
  store i32 0, i32* %5
  br label %"10"

"10":                                             ; preds = %"23", %entrypoint
  %9 = load i32, i32* %5
  %10 = icmp slt i32 %9, 10
  br i1 %10, label %"13", label %"26"

"13":                                             ; preds = %"10"
  %11 = load i32, i32* %5
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds [10 x i32], [10 x i32]* %2, i64 0, i64 %12
  store i32 0, i32* %13
  %14 = load i32, i32* %5
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i32 0, i64 %15
  store i32 0, i32* %16
  %17 = load i32, i32* %5
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %18
  store i32 0, i32* %19
  br label %"23"

"23":                                             ; preds = %"13"
  %20 = load i32, i32* %5
  %21 = add nsw i32 %20, 1
  store i32 %21, i32* %5
  br label %"10"

"26":                                             ; preds = %"10"
  store i32 0, i32* %6
  br label %"27"

"27":                                             ; preds = %"102", %"26"
  %22 = load i32, i32* %6
  %23 = icmp slt i32 %22, 800
  br i1 %23, label %"30", label %"105"

"30":                                             ; preds = %"27"
  store i32 0, i32* %7
  br label %"31"

"31":                                             ; preds = %"98", %"30"
  %24 = load i32, i32* %7
  %25 = icmp slt i32 %24, 800
  br i1 %25, label %"34", label %"101"

"34":                                             ; preds = %"31"
  %26 = load i32, i32* %6
  %27 = sext i32 %26 to i64
  %28 = getelementptr inbounds [800 x [800 x { i32, i32, i32 }]], [800 x [800 x { i32, i32, i32 }]]* @pixels, i64 0, i64 %27
  %29 = load i32, i32* %7
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds [800 x { i32, i32, i32 }], [800 x { i32, i32, i32 }]* %28, i32 0, i64 %30
  %32 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %31, i32 0, i32 0
  %33 = load i32, i32* %32
  %34 = icmp sge i32 %33, 0
  br i1 %34, label %"44", label %"97"

"44":                                             ; preds = %"34"
  %35 = load i32, i32* %6
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds [800 x [800 x { i32, i32, i32 }]], [800 x [800 x { i32, i32, i32 }]]* @pixels, i64 0, i64 %36
  %38 = load i32, i32* %7
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds [800 x { i32, i32, i32 }], [800 x { i32, i32, i32 }]* %37, i64 0, i64 %39
  %41 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %40, i32 0, i32 1
  %42 = load i32, i32* %41
  %43 = load i32, i32* %6
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds [800 x [800 x { i32, i32, i32 }]], [800 x [800 x { i32, i32, i32 }]]* @pixels, i64 0, i64 %44
  %46 = load i32, i32* %7
  %47 = sext i32 %46 to i64
  %48 = getelementptr inbounds [800 x { i32, i32, i32 }], [800 x { i32, i32, i32 }]* %45, i32 0, i64 %47
  %49 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %48, i32 0, i32 0
  %50 = load i32, i32* %49
  %51 = sext i32 %50 to i64
  %52 = getelementptr inbounds [10 x i32], [10 x i32]* %2, i64 0, i64 %51
  %53 = load i32, i32* %52
  %54 = add nsw i32 %53, %42
  store i32 %54, i32* %52
  %55 = load i32, i32* %6
  %56 = sext i32 %55 to i64
  %57 = getelementptr inbounds [800 x [800 x { i32, i32, i32 }]], [800 x [800 x { i32, i32, i32 }]]* @pixels, i64 0, i64 %56
  %58 = load i32, i32* %7
  %59 = sext i32 %58 to i64
  %60 = getelementptr inbounds [800 x { i32, i32, i32 }], [800 x { i32, i32, i32 }]* %57, i64 0, i64 %59
  %61 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %60, i32 0, i32 2
  %62 = load i32, i32* %61
  %63 = load i32, i32* %6
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds [800 x [800 x { i32, i32, i32 }]], [800 x [800 x { i32, i32, i32 }]]* @pixels, i64 0, i64 %64
  %66 = load i32, i32* %7
  %67 = sext i32 %66 to i64
  %68 = getelementptr inbounds [800 x { i32, i32, i32 }], [800 x { i32, i32, i32 }]* %65, i32 0, i64 %67
  %69 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %68, i32 0, i32 0
  %70 = load i32, i32* %69
  %71 = sext i32 %70 to i64
  %72 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %71
  %73 = load i32, i32* %72
  %74 = add nsw i32 %73, %62
  store i32 %74, i32* %72
  %75 = load i32, i32* %6
  %76 = sext i32 %75 to i64
  %77 = getelementptr inbounds [800 x [800 x { i32, i32, i32 }]], [800 x [800 x { i32, i32, i32 }]]* @pixels, i64 0, i64 %76
  %78 = load i32, i32* %7
  %79 = sext i32 %78 to i64
  %80 = getelementptr inbounds [800 x { i32, i32, i32 }], [800 x { i32, i32, i32 }]* %77, i64 0, i64 %79
  %81 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %80, i32 0, i32 0
  %82 = load i32, i32* %81
  %83 = sext i32 %82 to i64
  %84 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %83
  %85 = load i32, i32* %84
  %86 = add nsw i32 %85, 1
  store i32 %86, i32* %84
  br label %"97"

"97":                                             ; preds = %"44", %"34"
  br label %"98"

"98":                                             ; preds = %"97"
  %87 = load i32, i32* %7
  %88 = add nsw i32 %87, 1
  store i32 %88, i32* %7
  br label %"31"

"101":                                            ; preds = %"31"
  br label %"102"

"102":                                            ; preds = %"101"
  %89 = load i32, i32* %6
  %90 = add nsw i32 %89, 1
  store i32 %90, i32* %6
  br label %"27"

"105":                                            ; preds = %"27"
  store i32 0, i32* %8
  br label %"106"

"106":                                            ; preds = %"162", %"105"
  %91 = load i32, i32* %8
  %92 = icmp slt i32 %91, 10
  br i1 %92, label %"109", label %"165"

"109":                                            ; preds = %"106"
  %93 = load i32, i32* %8
  %94 = sext i32 %93 to i64
  %95 = getelementptr inbounds [10 x i32], [10 x i32]* %2, i64 0, i64 %94
  %96 = load i32, i32* %95
  %97 = load i32, i32* %8
  %98 = sext i32 %97 to i64
  %99 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %98
  %100 = load i32, i32* %99
  %101 = sdiv i32 %96, %100
  store i32 %101, i32* %1
  %102 = load i32, i32* %8
  %103 = sext i32 %102 to i64
  %104 = getelementptr inbounds [10 x { i32, i32, i32 }], [10 x { i32, i32, i32 }]* @points, i64 0, i64 %103
  %105 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %104, i32 0, i32 1
  %106 = load i32, i32* %105
  %107 = load i32, i32* %1
  %108 = icmp eq i32 %106, %107
  br i1 %108, label %"126", label %"129"

"126":                                            ; preds = %"109"
  %109 = load i32, i32* %0
  %110 = add nsw i32 %109, 1
  store i32 %110, i32* %0
  br label %"135"

"129":                                            ; preds = %"109"
  %111 = load i32, i32* %1
  %112 = load i32, i32* %8
  %113 = sext i32 %112 to i64
  %114 = getelementptr inbounds [10 x { i32, i32, i32 }], [10 x { i32, i32, i32 }]* @points, i64 0, i64 %113
  %115 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %114, i32 0, i32 1
  store i32 %111, i32* %115
  br label %"135"

"135":                                            ; preds = %"129", %"126"
  %116 = load i32, i32* %8
  %117 = sext i32 %116 to i64
  %118 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %117
  %119 = load i32, i32* %118
  %120 = load i32, i32* %8
  %121 = sext i32 %120 to i64
  %122 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %121
  %123 = load i32, i32* %122
  %124 = sdiv i32 %119, %123
  store i32 %124, i32* %1
  %125 = load i32, i32* %8
  %126 = sext i32 %125 to i64
  %127 = getelementptr inbounds [10 x { i32, i32, i32 }], [10 x { i32, i32, i32 }]* @points, i64 0, i64 %126
  %128 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %127, i32 0, i32 2
  %129 = load i32, i32* %128
  %130 = load i32, i32* %1
  %131 = icmp eq i32 %129, %130
  br i1 %131, label %"152", label %"155"

"152":                                            ; preds = %"135"
  %132 = load i32, i32* %0
  %133 = add nsw i32 %132, 1
  store i32 %133, i32* %0
  br label %"161"

"155":                                            ; preds = %"135"
  %134 = load i32, i32* %1
  %135 = load i32, i32* %8
  %136 = sext i32 %135 to i64
  %137 = getelementptr inbounds [10 x { i32, i32, i32 }], [10 x { i32, i32, i32 }]* @points, i64 0, i64 %136
  %138 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %137, i32 0, i32 2
  store i32 %134, i32* %138
  br label %"161"

"161":                                            ; preds = %"155", %"152"
  br label %"162"

"162":                                            ; preds = %"161"
  %139 = load i32, i32* %8
  %140 = add nsw i32 %139, 1
  store i32 %140, i32* %8
  br label %"106"

"165":                                            ; preds = %"106"
  %141 = load i32, i32* %0
  ret i32 %141
}

declare void @gl_start()

declare void @gl_put_pixel({ i32, i32, i32 }*)

declare void @gl_flush()
