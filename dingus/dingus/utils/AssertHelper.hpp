#pragma once

#define ASSERT_MSG(condition, message) assert((condition) || !message)
#define ASSERT_FAIL_MSG(message) assert(!message)
