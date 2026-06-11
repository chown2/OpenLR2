#pragma once

#include <array>
#include <filesystem>
#include <future>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

struct game;
struct sqlite3;
class CustomIR;

class CUSTOMIR_MANAGER {
public:
	CUSTOMIR_MANAGER() = default;
	CUSTOMIR_MANAGER operator=(const CUSTOMIR_MANAGER&) = delete;
	CUSTOMIR_MANAGER(const CUSTOMIR_MANAGER&) = delete;
	CUSTOMIR_MANAGER operator=(CUSTOMIR_MANAGER&&) = delete;
	CUSTOMIR_MANAGER(CUSTOMIR_MANAGER&&) = delete;
	~CUSTOMIR_MANAGER();
	void Initialize(const std::filesystem::path& directory);
	void Login();
	void SendScore(game& game, sqlite3* sql, int player);
private:
	std::vector<std::shared_ptr<CustomIR>> mModules;
	std::vector<std::future<void>> mSendThreads;
};
