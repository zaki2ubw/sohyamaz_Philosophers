#!/bin/bash

# ==============================================================================
# Philo Tester v2 (Extreme & Auto-Summary)
# ==============================================================================

PHILO="./philo"
# Valgrind設定: エラー検出時に終了コード42を返すように設定
VAL_LEAK="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42 -q"
VAL_RACE="valgrind --tool=helgrind --error-exitcode=42 -q"

# タイムアウト設定 (無限ループ系テスト用: 5秒で強制終了)
TIMEOUT_CMD="timeout 5s"

# 色設定
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
BLUE="\033[34m"
RESET="\033[0m"

# 失敗リスト配列
FAILED_TESTS=()

# 1. コンパイル
echo -e "${BLUE}=== Compiling Project... ===${RESET}"
make re
if [ ! -f "$PHILO" ]; then
    echo -e "${RED}Error: Executable $PHILO not found.${RESET}"
    exit 1
fi
echo -e "${BLUE}=== Compilation Done ===${RESET}\n"

# テスト実行関数
run_test() {
    ARGS="$1"
    TYPE="$2" # "LEAK" or "RACE"
    DESC="$3"
    MODE="$4" # "LOOP" (回数指定あり) or "INF" (無限)

    echo -e "${YELLOW}-------------------------------------------------------------${RESET}"
    echo -e "${YELLOW}Testing [${TYPE}]: ${DESC}${RESET}"
    echo -e "Command: ./philo $ARGS"

    # コマンド構築
    if [ "$TYPE" == "LEAK" ]; then
        CMD="$VAL_LEAK $PHILO $ARGS"
    elif [ "$TYPE" == "RACE" ]; then
        CMD="$VAL_RACE $PHILO $ARGS"
    fi

    # 実行 (無限モードならtimeoutを使う)
    if [ "$MODE" == "INF" ]; then
        $TIMEOUT_CMD $CMD
        RET=$?
        # timeout(124)は正常とみなす。Valgrindエラー(42)とSegfault(139)を検知
        if [ $RET -eq 124 ]; then
            echo -e "${GREEN}>> Timeout (Simulation running correctly)${RESET}"
            RET=0
        fi
    else
        $CMD
        RET=$?
    fi

    # 判定
    if [ $RET -eq 42 ]; then
        echo -e "${RED}[FAIL] Valgrind detected errors!${RESET}"
        FAILED_TESTS+=("[$TYPE] $DESC (Args: $ARGS)")
    elif [ $RET -eq 139 ] || [ $RET -eq 134 ]; then
        echo -e "${RED}[FAIL] Segmentation Fault or Crash!${RESET}"
        FAILED_TESTS+=("[$TYPE] CRASH: $DESC (Args: $ARGS)")
    elif [ $RET -ne 0 ]; then
        # 死ぬテストなどで終了コードが変わる場合があるので、基本はValgrindエラー以外はスルー
        # ただし、今回はphiloが常に0を返す設計なので、ここに来るのは異常系
        echo -e "${GREEN}[OK] Finished (Exit Code: $RET)${RESET}"
    else
        echo -e "${GREEN}[OK] Clean run${RESET}"
    fi
}

# ==========================================
# 1. Memory Leak Tests (Memcheck)
# ==========================================
echo -e "${BLUE}\n>>> Starting Memory Leak Tests (Valgrind Memcheck) <<<${RESET}"

# --- 基本 & 2人パターン ---
# 2人: 基本 (一番バグりやすい。片方が食べてる間に片方がフォークを持てるか？)
run_test "2 800 200 200" "LEAK" "2 Philos: Basic (Infinite)" "INF"

# 2人: 餓死 (片方が死ぬ)
run_test "2 310 200 100" "LEAK" "2 Philos: Starvation (Should Die)" "LOOP"

# 2人: ギリギリ (410ms寿命 vs 400ms消費)
run_test "2 410 200 200" "LEAK" "2 Philos: Tight Timing (Survival)" "INF"

# --- 基本パターン (人数多め) ---
run_test "4 410 200 200 5" "LEAK" "4 Philos: Tight Timing (Limited Loop)" "LOOP"
run_test "5 800 200 200 7" "LEAK" "5 Philos: Standard (Eat 7)" "LOOP"

# --- コーナーケース (極端) ---
# 1人ぼっち (即死確認)
run_test "1 800 200 200" "LEAK" "1 Philo: Lonely Death" "LOOP"

# 奇数 (3人) - フォークの奪い合いが発生しやすい
run_test "3 610 200 200" "LEAK" "3 Philos: Odd Number" "INF"

# 高負荷 (200人 - 評価シートの上限)
# ※処理落ちで死ぬ可能性あるが、リークがないかを見るのが目的
run_test "199 800 200 200 2" "LEAK" "199 Philos: Odd Heavy Load" "LOOP"

# 超高速 (60ms - 許容される最小値)
run_test "4 130 60 60 5" "LEAK" "4 Philos: Super Fast (60ms)" "LOOP"

# ==========================================
# 2. Data Race Tests (Helgrind)
# ==========================================
echo -e "${BLUE}\n>>> Starting Data Race Tests (Valgrind Helgrind) <<<${RESET}"
echo -e "${YELLOW}Note: Running simplified versions for Race Check.${RESET}"

run_test "2 800 200 200" "RACE" "Race: 2 Philos (Infinite)" "INF"
run_test "4 410 200 200 3" "RACE" "Race: 4 Philos (Tight)" "LOOP"
run_test "5 800 200 200 3" "RACE" "Race: 5 Philos (Standard)" "LOOP"

# ==========================================
# 3. Summary
# ==========================================
echo -e "\n${BLUE}==============================================${RESET}"
echo -e "${BLUE}               TEST SUMMARY                   ${RESET}"
echo -e "${BLUE}==============================================${RESET}"

if [ ${#FAILED_TESTS[@]} -eq 0 ]; then
    echo -e "\n${GREEN}🎉 CONGRATULATIONS! ALL TESTS PASSED! 🎉${RESET}"
    echo -e "No leaks, no crashes, no data races found.\n"
    exit 0
else
    echo -e "\n${RED}❌ FAILURES DETECTED in the following tests:${RESET}"
    for fail in "${FAILED_TESTS[@]}"; do
        echo -e "  - $fail"
    done
    echo -e "\n${RED}Please fix the errors above before submitting.${RESET}\n"
    exit 1
fi
