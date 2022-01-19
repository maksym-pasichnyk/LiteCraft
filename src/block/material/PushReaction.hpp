#pragma once

#pragma push_macro("IGNORE")
#undef IGNORE

enum class PushReaction {
    NORMAL,
    DESTROY,
    BLOCK,
    IGNORE,
    PUSH_ONLY
};

#pragma pop_macro("IGNORE")
