#pragma once

#include <variant>

template <typename... Ts, typename... Fs>
static auto match(std::variant<Ts...>& v, Fs&&... fs) -> decltype(auto) {
	struct matches : Fs... {
		using Fs::operator()...;
	};
	return std::visit(matches{ std::forward<Fs>(fs)... }, v);
}

template <typename... Ts, typename... Fs>
static auto match(std::variant<Ts...>&& v, Fs&&... fs) -> decltype(auto) {
	struct matches : Fs... {
		using Fs::operator()...;
	};
	return std::visit(matches{ std::forward<Fs>(fs)... }, std::move(v));
}

template <typename... Ts, typename... Fs>
static auto match(const std::variant<Ts...>& v, Fs&&... fs) -> decltype(auto) {
	struct matches : Fs... {
		using Fs::operator()...;
	};
	return std::visit(matches{ std::forward<Fs>(fs)... }, v);
}