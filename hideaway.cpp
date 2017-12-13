#include <mutex>
#include <chrono>
#include <thread>
#include <future>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdint>

extern "C" {
#include <linux/input.h>
}

inline int read_event(input_event &event) {
    return std::fread(&event, sizeof(input_event), 1, stdin) == 1;
}

inline void write_event(const input_event &event) {
    if (std::fwrite(&event, sizeof(input_event), 1, stdout) != 1)
        std::exit(EXIT_FAILURE);
}

inline void move(std::int32_t x, std::int32_t y) {
    write_event({{}, EV_REL, REL_X, x});
    write_event({{}, EV_REL, REL_Y, y});
    write_event({{}, EV_SYN, SYN_REPORT, 0});
}

int main(int argc, char *argv[]) {
    using std::chrono::system_clock;
    using std::this_thread::sleep_for;

    if (argc != 6)
        return std::fprintf(
                   stderr,
                   "usage %s <seconds> <away x> <away y> <back x> <back y>\n",
                   argv[0]),
               EXIT_FAILURE;

    std::setbuf(stdin, nullptr), std::setbuf(stdout, nullptr);

    const auto seconds        = std::chrono::seconds(std::stoi(argv[1]));
    const std::int32_t away_x = std::stoi(argv[2]);
    const std::int32_t away_y = std::stoi(argv[3]);
    const std::int32_t back_x = std::stoi(argv[4]);
    const std::int32_t back_y = std::stoi(argv[5]);
    auto last_event           = system_clock::now();
    bool hidden               = false;
    std::mutex move_mutex;
    input_event input;

    auto timer = std::async(
        std::launch::async,
        [seconds, away_x, away_y, &hidden, &last_event, &move_mutex] {
            for (;;) {
                {
                    std::lock_guard<std::mutex> lock{move_mutex};
                    if (!hidden && system_clock::now() - last_event > seconds) {
                        move(away_x, away_y);
                        last_event = system_clock::now();
                        hidden     = true;
                    }
                }
                sleep_for(seconds);
            }
        });
    while (read_event(input)) {
        std::lock_guard<std::mutex> lock{move_mutex};
        if (hidden) {
            move(back_x, back_y);
            hidden = false;
        }
        last_event = system_clock::now();
    }
}
