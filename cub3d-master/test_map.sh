#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

PROGRAM="./cub3D"
PASS=0
FAIL=0
TOTAL=0

run_test()
{
    local test_name="$1"
    local map_file="$2"
    local expected="$3"  # "pass" veya "fail"

    TOTAL=$((TOTAL + 1))

    if [ "$expected" = "fail" ]; then
        # HATA vermesi beklenen mapler: timeout olmadan çalıştır
        # Eğer program hemen çıkıyorsa (pencere açmadan) exit code != 0 olmalı
        output=$(timeout 2s "$PROGRAM" "$map_file" 2>&1)
        exit_code=$?

        # timeout=124, normal hata çıkışı != 0
        # Eğer timeout olduysa (124) program pencere açtı = geçmemesi lazımdı = FAIL
        if [ $exit_code -eq 124 ]; then
            echo -e "${RED}[FAIL]${NC} $test_name (program did not reject - opened window)"
            FAIL=$((FAIL + 1))
        elif [ $exit_code -ne 0 ]; then
            echo -e "${GREEN}[PASS]${NC} $test_name (correctly rejected)"
            PASS=$((PASS + 1))
        else
            echo -e "${RED}[FAIL]${NC} $test_name (exit 0 - should have failed)"
            FAIL=$((FAIL + 1))
        fi

    else
        # BAŞARILI olması beklenen mapler: sadece parse kontrolü
        # Program pencere açmadan önce parse hatası verip vermediğini kontrol et
        output=$(timeout 2s "$PROGRAM" "$map_file" 2>&1)
        exit_code=$?

        # timeout=124 ise program pencere açtı = parse başarılı = PASS
        # exit 0 da parse başarılı demek
        if [ $exit_code -eq 124 ] || [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}[PASS]${NC} $test_name"
            PASS=$((PASS + 1))
        else
            echo -e "${RED}[FAIL]${NC} $test_name (exit: $exit_code)"
            echo -e "       ${YELLOW}Output: $output${NC}"
            FAIL=$((FAIL + 1))
        fi
    fi
}

print_header()
{
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}  $1${NC}"
    echo -e "${BLUE}========================================${NC}"
}

# ============================================================
print_header "ARGUMENT TESTS"
# ============================================================

TOTAL=$((TOTAL + 1))
output=$("$PROGRAM" 2>&1); ec=$?
if [ $ec -ne 0 ]; then
    echo -e "${GREEN}[PASS]${NC} No arguments"
    PASS=$((PASS + 1))
else
    echo -e "${RED}[FAIL]${NC} No arguments"
    FAIL=$((FAIL + 1))
fi

TOTAL=$((TOTAL + 1))
output=$(timeout 2s "$PROGRAM" maps/good/square_map.cub maps/good/square_map.cub 2>&1); ec=$?
if [ $ec -ne 0 ] && [ $ec -ne 124 ]; then
    echo -e "${GREEN}[PASS]${NC} Too many arguments"
    PASS=$((PASS + 1))
else
    echo -e "${RED}[FAIL]${NC} Too many arguments"
    FAIL=$((FAIL + 1))
fi

# ============================================================
print_header "EXTENSION TESTS"
# ============================================================
run_test "Wrong extension (.buc)"        "maps/bad/filetype_wrong.buc"    "fail"
run_test "Missing extension"             "maps/bad/filetype_missing"       "fail"
run_test "Hidden file (.asda.cub)"       "maps/.asda.cub"                 "fail"
run_test "Non-existent file"             "maps/bad/non_existent.cub"      "fail"
run_test "Directory instead of file"     "maps/bad"                       "fail"
run_test "File ending with letter"       "maps/bad/file_letter_end.cub"   "fail"

# ============================================================
print_header "TEXTURE TESTS"
# ============================================================
run_test "Missing texture paths"         "maps/bad/textures_missing.cub"    "fail"
run_test "No textures at all"            "maps/bad/textures_none.cub"       "fail"
run_test "Duplicate textures"            "maps/bad/textures_duplicates.cub" "fail"
run_test "Invalid texture path"          "maps/bad/textures_invalid.cub"    "fail"
run_test "Texture is directory"          "maps/bad/textures_dir.cub"        "fail"
run_test "Texture not xpm"               "maps/bad/textures_not_xpm.cub"    "fail"
run_test "Textures after map"            "maps/bad/texture_after_map.cub" "fail"

# ============================================================
print_header "COLOR TESTS"
# ============================================================
run_test "Missing floor color"           "maps/bad/color_missing_floor_rgb.cub"   "fail"
run_test "Missing ceiling color"         "maps/bad/color_missing_ceiling_rgb.cub" "fail"
run_test "Missing both colors"           "maps/bad/color_missing.cub"      "fail"
run_test "No colors at all"              "maps/bad/color_none.cub"         "fail"
run_test "Invalid RGB values"            "maps/bad/color_invalid_rgb.cub"  "fail"
run_test "Trailing comma F"              "maps/bad/color_trailing_comma_f.cub"  "fail"
run_test "Trailing comma C"              "maps/bad/color_trailing_comma_c.cub"  "fail"
run_test "Color value 256"               "maps/bad/color_256.cub"       "fail"
run_test "Color value -1"                "maps/bad/color_negative.cub"  "fail"
run_test "Color extra comma middle"      "maps/bad/color_double_comma.cub" "fail"
run_test "Color only 2 values"           "maps/bad/color_only_two.cub"  "fail"
run_test "Color 4 values"                "maps/bad/color_four_values.cub" "fail"
run_test "Color with spaces"             "maps/good/color_with_spaces.cub" "pass"
run_test "Color 000000000000255"         "maps/good/color_leading_zeros.cub" "pass"
run_test "Color 0,0,0"                   "maps/good/color_black.cub"    "pass"
run_test "Color 255,255,255"             "maps/good/color_white.cub"    "pass"

# ============================================================
print_header "MAP STRUCTURE TESTS"
# ============================================================
run_test "Empty file"                    "maps/bad/empty.cub"              "fail"
run_test "No map"                        "maps/bad/map_missing.cub"        "fail"
run_test "Map only"                      "maps/bad/map_only.cub"           "fail"
run_test "Map too small"                 "maps/bad/map_too_small.cub"      "fail"
run_test "Map not at end (first)"        "maps/bad/map_first.cub"          "fail"
run_test "Map in middle"                 "maps/bad/map_middle.cub"         "fail"
run_test "Map with invalid chars"        "maps/bad/map_invalid_char.cub" "fail"
run_test "Map with tab chars"            "maps/bad/map_with_tab.cub"     "fail"
run_test "Empty line in map body"        "maps/bad/map_empty_line_middle.cub" "fail"

# ============================================================
print_header "WALL HOLE TESTS"
# ============================================================
run_test "Hole in north wall"            "maps/bad/wall_hole_north.cub"    "fail"
run_test "Hole in south wall"            "maps/bad/wall_hole_south.cub"    "fail"
run_test "Hole in east wall"             "maps/bad/wall_hole_east.cub"     "fail"
run_test "Hole in west wall"             "maps/bad/wall_hole_west.cub"     "fail"
run_test "No walls at all"               "maps/bad/wall_none.cub"          "fail"
run_test "Hole via space inside map"     "maps/bad/wall_hole_space.cub" "fail"
run_test "Unreachable area open"         "maps/bad/unreachable_open.cub" "fail"
run_test "Unreachable area enclosed"     "maps/good/unreachable_enclosed.cub" "pass"

# ============================================================
print_header "PLAYER TESTS"
# ============================================================
run_test "No player"                     "maps/bad/player_none.cub"        "fail"
run_test "Multiple players"              "maps/bad/player_multiple.cub"    "fail"
run_test "Player on edge"                "maps/bad/player_on_edge.cub"     "fail"
run_test "Player facing North (N)"       "maps/good/player_north.cub"  "pass"
run_test "Player facing South (S)"       "maps/good/player_south.cub"  "pass"
run_test "Player facing East (E)"        "maps/good/player_east.cub"   "pass"
run_test "Player facing West (W)"        "maps/good/player_west.cub"   "pass"
run_test "Player top position"           "maps/good/test_pos_top.cub"      "pass"
run_test "Player bottom position"        "maps/good/test_pos_bottom.cub"   "pass"
run_test "Player left position"          "maps/good/test_pos_left.cub"     "pass"
run_test "Player right position"         "maps/good/test_pos_right.cub"    "pass"

# ============================================================
print_header "WHITESPACE TESTS"
# ============================================================
run_test "Map with whitespace"           "maps/good/test_whitespace.cub"   "pass"
run_test "Extra spaces in texture path"  "maps/good/texture_extra_spaces.cub" "pass"
run_test "Extra newlines before map"     "maps/good/extra_newlines.cub" "pass"

# ============================================================
print_header "GOOD MAP TESTS"
# ============================================================
run_test "Square map"                    "maps/good/square_map.cub"        "pass"
run_test "Subject map"                   "maps/good/subject_map.cub"       "pass"
run_test "Cheese maze"                   "maps/good/cheese_maze.cub"       "pass"
run_test "Dungeon"                       "maps/good/dungeon.cub"           "pass"
run_test "Library"                       "maps/good/library.cub"           "pass"
run_test "Matrix"                        "maps/good/matrix.cub"            "pass"

# ============================================================
echo -e "\n${BLUE}========================================${NC}"
echo -e "  RESULTS: ${GREEN}$PASS PASS${NC} | ${RED}$FAIL FAIL${NC} | TOTAL: $TOTAL"
echo -e "${BLUE}========================================${NC}\n"

[ $FAIL -eq 0 ] && exit 0 || exit 1