#pragma once
#include "default_includes.hpp"
#include <regex>

inline std::string format_error_string(std::string value) {

  return std::regex_replace(value, std::regex("\n"), "\n|");
}

template <typename T>
std::string add_context_to_error(std::string to_add,
                                 std::expected<T, std::string> error_value) {
  std::string previous_errors =
      std::regex_replace(error_value.error(), std::regex("\n"), "\n  ");
  return format_error_string(to_add) + "\n" + "|_" + previous_errors;
}

template <typename T>
std::expected<T, std::string> format_error(std::string value) {
  return std::unexpected(format_error_string(value));
}

#define UNWRAP_FMT(expr, fmt_str, ...)                                         \
  ({                                                                           \
    auto __tmp = (expr);                                                       \
    if (!__tmp.has_value())                                                    \
      return std::unexpected(                                                  \
          add_context_to_error(std::format(fmt_str, __VA_ARGS__), __tmp));     \
    std::move(__tmp.value());                                                  \
  })
#define UNWRAP_CTX(expr, ctx)                                                  \
  ({                                                                           \
    auto __tmp = (expr);                                                       \
    if (!__tmp.has_value())                                                    \
      return std::unexpected(add_context_to_error(ctx, __tmp));                \
    std::move(__tmp.value());                                                  \
  })

#define UNWRAP(expr)                                                           \
  ({                                                                           \
    auto __tmp = (expr);                                                       \
    if (!__tmp.has_value())                                                    \
      return std::unexpected(__tmp.error());                                   \
    std::move(__tmp.value());                                                  \
  })

#define BAIL(ctx) return format_error(ctx);
#define BAIL_FMT(fmt_str, ...)                                                 \
  return unexpected(std::format(fmt_str, __VA_ARGS__));

#define TRY_CTX(result, ctx)                                                   \
  if (!(result)) {                                                             \
    return std::unexpected(add_context_to_error((ctx), (result)));             \
  }

#define TRY(result)                                                            \
  if (!(result)) {                                                             \
    return std::unexpected(result.error());                                    \
  }

#define TRY_FMT(result, fmt_str, ...)                                          \
  if (!(result)) {                                                             \
    return std::unexpected(                                                    \
        add_context_to_error(std::format(fmt_str, __VA_ARGS__), (result)));    \
  }
