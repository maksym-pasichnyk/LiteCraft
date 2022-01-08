#include <Json.hpp>
#include <glm/fwd.hpp>

template <>
auto Json::Into<std::string>::into(const Json& obj) -> Result {
    return obj.as_string();
}

template <>
auto Json::Into<bool>::into(const Json& obj) -> Result {
    return obj.as_bool();
}

template <>
auto Json::Into<glm::f32>::into(const Json& obj) -> Result {
    return obj.as_f64();
}

template <>
auto Json::Into<glm::f64>::into(const Json& obj) -> Result {
    return obj.as_f64();
}

template <>
auto Json::Into<glm::i8>::into(const Json& obj) -> Result {
    return obj.as_i64();
}

template <>
auto Json::Into<glm::i16>::into(const Json& obj) -> Result {
    return obj.as_i64();
}

template <>
auto Json::Into<glm::i32>::into(const Json& obj) -> Result {
    return obj.as_i64();
}

template <>
auto Json::Into<glm::i64>::into(const Json& obj) -> Result {
    return obj.as_i64();
}

template <>
auto Json::Into<glm::u8>::into(const Json& obj) -> Result {
    return obj.as_i64();
}

template <>
auto Json::Into<glm::u16>::into(const Json& obj) -> Result {
    return obj.as_i64();
}

template <>
auto Json::Into<glm::u32>::into(const Json& obj) -> Result {
    return obj.as_i64();
}

template <>
auto Json::Into<glm::u64>::into(const Json& obj) -> Result {
    return obj.as_i64();
}

template<>
auto Json::From<bool>::from(const bool& val) -> Json {
    return Json::Bool{val};
}

template<>
auto Json::From<glm::i8>::from(const Value& value) -> Self {
    return Json::Number{static_cast<glm::i64>(value)};
}

template<>
auto Json::From<glm::i16>::from(const Value& value) -> Self {
    return Json::Number{static_cast<glm::i64>(value)};
}

template<>
auto Json::From<glm::i32>::from(const Value& value) -> Self {
    return Json::Number{static_cast<glm::i64>(value)};
}

template<>
auto Json::From<glm::i64>::from(const Value& value) -> Self {
    return Json::Number{static_cast<glm::i64>(value)};
}

template<>
auto Json::From<glm::u8>::from(const Value& value) -> Self {
    return Json::Number{static_cast<glm::i64>(value)};
}

template<>
auto Json::From<glm::u16>::from(const Value& value) -> Self {
    return Json::Number{static_cast<glm::i64>(value)};
}

template<>
auto Json::From<glm::u32>::from(const Value& value) -> Self {
    return Json::Number{static_cast<glm::i64>(value)};
}

template<>
auto Json::From<glm::u64>::from(const Value& value) -> Self {
    return Json::Number{static_cast<glm::i64>(value)};
}

template<>
auto Json::From<glm::f32>::from(const Value &value) -> Self {
    return Json::Number{static_cast<double>(value)};
}
template<>
auto Json::From<glm::f64>::from(const Value &value) -> Self {
    return Json::Number{static_cast<double>(value)};
}

struct Json::Read::Internal {
	struct End {};
	struct Comma {};
	struct Column {};
	struct BeginArray {};
	struct EndArray {};
	struct BeginObject {};
	struct EndObject {};

	using String = Json::String;
	using Number = Json::Number;
	using Bool = Json::Bool;
	using Null = Json::Null;

	using Token = std::variant<
		End,
		Comma,
		Column,
		BeginArray,
		EndArray,
		BeginObject,
		EndObject,

		String,
		Number,
		Bool,
		Null
	>;

	template <typename Fn, typename... Args>
	static auto take_while(std::istream& stream, Fn&& fn, Args&&... args) {
		while (!stream.eof() && fn(stream.peek(), std::forward<Args>(args)...)) {
			stream.get();
		}
	}

	static auto read_string(std::istream& stream, const char ch) /*noexcept*/ -> tl::optional<Token> {
		std::string out{};

		stream.get();

		take_while(stream, [&stream, ch, &out](char c) -> bool {
			if (c == ch || c == '\n') {
				return false;
			}
			if (c == '\\') {
				stream.get();
				if (stream.eof()) {
					return false;
				}
				switch (const auto s = static_cast<char>(stream.peek())) {
					case 'n': out.push_back('\n'); break;
					case 'r': out.push_back('\r'); break;
					case 't': out.push_back('\t'); break;
					case 'v': out.push_back('\v'); break;
					default: out.push_back(s); break;
				}
				return true;
			}
			out.push_back(c);
			return true;
		});

		if (stream.peek() != ch) {
//				fmt::print("unterminated string literal");
			return tl::nullopt;
		}

		stream.get();

		return std::move(out);
	}

	static auto read_number(std::istream& stream) -> tl::optional<Token> {
		const auto sign = stream.peek() == '-';
		if (sign) {
			stream.get();
		}

		std::string out{};

		bool flag = true;
		take_while(stream, [&flag, &out](char c) -> bool {
			if (isdigit(c) || (c == '.' && std::exchange(flag, false))) {
				out.push_back(c);
				return true;
			}
			return false;
		});

        if (stream.peek() == 'e' || stream.peek() == 'E') {
            flag = true;

            out.push_back(stream.peek());
            stream.get();

            if (stream.peek() == '-' || stream.peek() == '+') {
                out.push_back(stream.peek());
                stream.get();
            }
            take_while(stream, [&out](char c) -> bool {
                if (isdigit(c)) {
                    out.push_back(c);
                    return true;
                }
                return false;
            });
        }

		if (flag) {
			const auto num = std::stoi(out, nullptr);
			return Number{static_cast<int64_t>(sign ? -num : num)};
		} else {
			const auto num = std::stod(out, nullptr);
			return Number{static_cast<double>(sign ? -num : num)};
		}
	}

	static auto read_ident(std::istream& stream) -> tl::optional<Token> {
		std::string out{};

		using namespace std::string_view_literals;

		take_while(stream, [&out](char c) -> bool {
			if (isalnum(c) || (c == '_')) {
				out.push_back(c);
				return true;
			}
			return false;
		});

		if (out == "true"sv) {
			return Bool{ true };
		} else if (out == "false"sv) {
			return Bool{ false };
		} else if (out == "null"sv) {
			return Null{};
		} else {
			return tl::nullopt;
		}
	}

	static void nextline(std::istream& stream, char c) /*noexcept*/ {
		stream.get();
		if (!stream.eof() && (c != stream.peek()) && isnewline(stream.peek())) {
			stream.get();
		}
	}

	static auto next_token(std::istream& stream) /*noexcept*/ -> tl::optional<Token> {
		while (!stream.eof()) {
			switch (char c = stream.peek()) {
				case '\n': case '\r':
					nextline(stream, c);
					continue;
				case ' ': case '\t': case '\v': case '\f':
					stream.get();
					continue;
                case '/':
                    stream.get();
                    if (stream.peek() == '/') {
                        stream.get();
                        while (!stream.eof()) {
                            if (isnewline(stream.peek())) {
                                nextline(stream, stream.peek());
                                break;
                            } else {
                                stream.get();
                            }
                        }
                        continue;
                    }
                    return tl::nullopt;
				case '{':
					stream.get();
					return BeginObject{};
				case '}':
					stream.get();
					return EndObject{};
				case '[':
					stream.get();
					return BeginArray{};
				case ']':
					stream.get();
					return EndArray{};
				case ':':
					stream.get();
					return Column{};
				case ',':
					stream.get();
					return Comma{};
				case '"': case '\'':
					return read_string(stream, c);
				case '0': case '1': case '2': case '3': case '4':
				case '5': case '6': case '7': case '8': case '9': case '-':
					return read_number(stream);
				default:
					if (isalpha(c) || (c == '_')) {
						return read_ident(stream);
					}
					return tl::nullopt;
			}
		}
		return End{};
	}

	static auto parse(std::istream& stream, const Token& in) /*noexcept*/ -> tl::optional<Json> {
		return match(in,
			[&stream](BeginArray) -> tl::optional<Json> {
				auto tk = next_token(stream);
                if (!tk) {
                    return tl::nullopt;
                }

				if (is<EndArray>(*tk)) {
					return Json::Array{};
				}

				auto out = Json::Array{};
				while (true) {
                    auto e = parse(stream, *tk);
                    if (!e) {
                        return tl::nullopt;
                    }
					out.emplace_back(std::move(*e));
					tk = next_token(stream);
                    if (!tk) {
                        return tl::nullopt;
                    }
					if (is<EndArray>(*tk)) {
						return std::move(out);
					}
					if (!is<Comma>(*tk)) {
						fmt::print("Json: syntax error");
						return tl::nullopt;
					}
					tk = next_token(stream);
                    if (!tk) {
                        return tl::nullopt;
                    }
				}
			},
			[&stream](BeginObject) -> tl::optional<Json> {
				auto tk = next_token(stream);
                if (!tk) {
                    return tl::nullopt;
                }
				if (is<EndObject>(*tk)) {
					return Json::Object{};
				}

				auto out = Json::Object{};
				while (true) {
                    if (!is<String>(*tk)) {
                        return tl::nullopt;
                    }
					auto name = std::move(std::get<std::string>(*tk));
					tk = next_token(stream);
                    if (!tk) {
                        return tl::nullopt;
                    }
					if (!is<Column>(*tk)) {
						fmt::print("Json: syntax error");
						return tl::nullopt;
					}
					tk = next_token(stream);
                    if (!tk) {
                        return tl::nullopt;
                    }
                    auto e = parse(stream, *tk);
                    if (!e) {
                        return tl::nullopt;
                    }
					out.emplace(std::move(name), std::move(*e));
					tk = next_token(stream);
                    if (!tk) {
                        return tl::nullopt;
                    }
					if (is<EndObject>(*tk)) {
						return std::move(out);
					}
					if (!is<Comma>(*tk)) {
						fmt::print("Json: syntax error");
						return tl::nullopt;
					}
					tk = next_token(stream);
                    if (!tk) {
                        return tl::nullopt;
                    }
				}
			},
			[](const String& val) -> tl::optional<Json> {
				return val;
			},
			[](const Number& val) -> tl::optional<Json> {
				return val;
			},
			[](const Bool& val) -> tl::optional<Json> {
				return val;
			},
			[](const Null& val) -> tl::optional<Json> {
				return val;
			},
			[](const auto& val) -> tl::optional<Json> {
				return tl::nullopt;
			}
		);
	}

	template <typename T>
	static auto is(const Token& tk) -> bool {
		return std::get_if<T>(&tk) != nullptr;
	}

	static auto isnewline(const char c) /*noexcept*/ -> bool {
		return (c == '\n') || (c == '\r');
	}

    static auto read(std::istream& stream) /*noexcept*/ -> tl::optional<Json> {
        return next_token(stream).and_then([&stream](auto&& o) {
            return parse(stream, o);
        });
    }
};

auto Json::Read::read(std::istream& stream) /*noexcept*/ -> tl::optional<Json> {
    return Internal::read(stream);
}

void Json::Dump::pack(std::ostream &out, const Json &obj) {
    match(obj.m_storage,
      [&out](const Json::Null&) {
        out << "null";
      },
      [&out](const Json::Bool& v) {
        out << (v ? "true" : "false");
      },
      [&out](const Json::Number& v) {
        return match(v, [&out](auto v) { out << v; });
      },
      [&out](const Json::String& v) {
        out << '"' << v << '"';
      },
      [&out](const Json::Array &arr) {
        out << '[';
        if (!arr.empty()) {
            pack(out, *arr.begin());

            if (arr.size() > 1) {
                const auto _begin = std::next(arr.begin());
                const auto _end = arr.end();

                for (auto v = _begin; v != _end; v++) {
                    out << ',';
                    pack(out, *v);
                }
            }
        }
        out << ']';
      },
      [&out](const Json::Object &obj) {
        out << '{';
        if (!obj.empty()) {
            auto first = obj.begin();
            out << fmt::format(R"("{}": )", first->first);
            pack(out, first->second);

            if (obj.size() > 1) {
                const auto _begin = std::next(obj.begin());
                const auto _end = obj.end();

                for (auto v = _begin; v != _end; v++) {
                    out << ',';
                    out << fmt::format(R"("{}": )", v->first);
                    pack(out, v->second);
                }
            }
        }
        out << '}';
      },
      [&out](const auto &) {}
    );
}

void Json::Dump::dump(std::ostream &out, const Json &obj, int ident) {
    match(obj.m_storage,
      [&out](const Json::Null&) {
        out << "null";
      },
      [&out](const Json::Bool& v) {
        out << (v ? "true" : "false");
      },
      [&out](const Json::Number& v) {
        return match(v, [&out](auto v) { out << v; });
      },
      [&out](const Json::String& v) {
        out << '"' << v << '"';
      },
      [&out, ident](const Json::Array &arr) {
        out << '[';
        if (!arr.empty()) {
            out << std::endl << fmt::format(R"({:{}})", "", ident + 4);
            dump(out, *arr.begin(), ident + 4);

            if (arr.size() > 1) {
                const auto _begin = std::next(arr.begin());
                const auto _end = arr.end();

                for (auto v = _begin; v != _end; v++) {
                    out << ',' << std::endl << fmt::format(R"({:{}})", "", ident + 4);
                    dump(out, *v, ident + 4);
                }
            }
            out << std::endl << fmt::format(R"({:{}})", "", ident);
        }
        out << ']';
      },
      [&out, ident](const Json::Object &obj) {
        out << '{';
        if (!obj.empty()) {
            out << std::endl;
            auto first = obj.begin();
            out << fmt::format(R"({:{}}"{}": )", "", ident + 4, first->first);
            dump(out, first->second, ident + 4);

            if (obj.size() > 1) {
                const auto _begin = std::next(obj.begin());
                const auto _end = obj.end();

                for (auto v = _begin; v != _end; v++) {
                    out << ',' << std::endl;
                    out << fmt::format(R"({:{}}"{}": )", "", ident + 4, v->first);
                    dump(out, v->second, ident + 4);
                }
            }
            out << std::endl << fmt::format(R"({:{}})", "", ident);
        }
        out << '}';
      },
      [&out](const auto &) {}
    );
}
