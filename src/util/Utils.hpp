#pragma once

struct Utils {
    static constexpr auto is_client() noexcept -> bool {
#ifdef DEDICATED_SERVER
        return false;
#else
        return true;
#endif
    }

    static constexpr auto is_server() noexcept -> bool {
        return !is_client();
    }
};