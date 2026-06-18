CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
SRC = src/main.cpp src/sphere.cpp src/world.cpp src/camera.cpp src/vec3.cpp src/ray.cpp
TARGET = raytracer.exe
INPUT_DIR = inputs
OUTPUT_DIR = outputs

.PHONY: all clean run example1 example2 example3

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

run: all
	@mkdir -p $(OUTPUT_DIR) 2> /dev/null || true
	./$(TARGET) $(INPUT_DIR)/example1.txt $(OUTPUT_DIR)/example1.ppm

example1: all
	@mkdir -p $(OUTPUT_DIR) 2> /dev/null || true
	./$(TARGET) $(INPUT_DIR)/example1.txt $(OUTPUT_DIR)/example1.ppm

example2: all
	@mkdir -p $(OUTPUT_DIR) 2> /dev/null || true
	./$(TARGET) $(INPUT_DIR)/example2.txt $(OUTPUT_DIR)/example2.ppm

example3: all
	@mkdir -p $(OUTPUT_DIR) 2> /dev/null || true
	./$(TARGET) $(INPUT_DIR)/example3.txt $(OUTPUT_DIR)/example3.ppm

example1080: all
	@mkdir -p $(OUTPUT_DIR) 2> /dev/null || true
	./$(TARGET) $(INPUT_DIR)/example_1920x1080.txt $(OUTPUT_DIR)/example_1920x1080.ppm

example720: all
	@mkdir -p $(OUTPUT_DIR) 2> /dev/null || true
	./$(TARGET) $(INPUT_DIR)/example_1280x720.txt $(OUTPUT_DIR)/example_1280x720.ppm

TEST_SRC = tests/test_vec3.cpp tests/test_ray.cpp tests/test_sphere.cpp tests/test_world.cpp tests/test_camera.cpp

.PHONY: all clean run example1 example2 example3 example1080 example720 test

TEST_BINARIES = $(patsubst tests/%.cpp,tests/%,$(TEST_SRC))

test: all $(TEST_BINARIES)
	@for testbin in $(TEST_BINARIES); do \
		printf "Running $$testbin...\n"; \
		./$$testbin || exit 1; \
	done

tests/%: tests/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< src/vec3.cpp src/ray.cpp src/camera.cpp src/world.cpp src/sphere.cpp -I src

clean:
	rm -f $(TARGET) $(OUTPUT_DIR)/*.ppm $(TEST_BINARIES)
