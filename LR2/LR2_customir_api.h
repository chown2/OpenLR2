#pragma once

#include <string>
#include <array>

#ifdef _WIN32
#define OLR2_IR_API __cdecl
#define OLR2_IR_EXPORT __declspec(dllexport)
#else
#define OLR2_IR_API
#define OLR2_IR_EXPORT
#endif // _WIN32

struct IRScoreV1 {
	struct SONG {
		std::string hash;
		std::string title;
		std::string subtitle;
		std::string genre;
		std::string artist;
		std::string subartist;
		int maxBPM{};
		int minBPM{};
		int longnote{};
		int random{};
		int judge{};
		int courseStageCount{};
		int courseType{};
	} song{};
	struct SETTINGS {
		int gaugeOption{};
		std::array<int, 2> random{};
		int autokey{};
		std::array<int, 2> assist{};
		int dpflip{};
		int hsfix{};
		std::array<int, 2> randSC{};
		std::array<int, 2> randFix{};
		int m_softlanding{};
		int m_addmine{};
		int m_addlong{};
		int m_earthquake{};
		int m_tornado{};
		int m_superloop{};
		int m_gambol{};
		int m_char{};
		int m_heartbeat{};
		int m_loudness{};
		int m_addnote{};
		int m_nabeatsu{};
		int m_accel{};
		int m_sincurve{};
		int m_wave{};
		int m_spiral{};
		int m_sidejump{};
		int is_extra{};
		int m_extra{};
		char m_lunaris{};
		bool m_gas{};
		int gomiscore{};
		int disablecurspeedchange{};
	} settings{};
	struct STATE {
		int player{};
		int keymode{};
		int randomseed{};
		double freqSpeedMultiplier{};
		double song_runtime{};
		char isNosave{};
		char isForceEasy{};
		char isCourse{};
		int courseStageNow{};
		int notes_total{};
	} state{};
	struct JUDGEMENTS {
		unsigned int epg{};
		unsigned int lpg{};
		unsigned int egr{};
		unsigned int lgr{};
		unsigned int egd{};
		unsigned int lgd{};
		unsigned int ebd{};
		unsigned int lbd{};
		unsigned int epr{};
		unsigned int lpr{};
		unsigned int cb{};
		unsigned int fast{};
		unsigned int slow{};
		unsigned int notes_played{};
		unsigned int notes_total{};
	};
	JUDGEMENTS judgements_total{};
	std::array<JUDGEMENTS, 20> judgements_column{};
	unsigned int max_combo{};
	std::array<double, 6> HP{};
	int gaugeType{};
	int moneyscore{};
	int exscore{};
	double rate{};
	int clearType{};
	int inputType{};
	struct GRAPHDATA {
		std::array<std::array<int, 1000>, 6> hp{};
		std::array<int, 1000> combo{};
		std::array<int, 1000> exscore{};
		std::array<int, 1000> rate{};
	} graphs{};
};

enum class SendScoreStatus: int {
	Ok = 0,
	Retry,
	Fail,
};

struct MethodTable {
	// Mandatory method. Module name must be unique among loaded modules.
	const char*(OLR2_IR_API* GetName)() = nullptr;
	// Maybe parse some configuration file there, and perform URL request to your IR for login.
	// This method is ran at game initialization synchronously.
	// Can be used for general initialization.
	bool(OLR2_IR_API* LoginV1)() = nullptr;
	// Ran on its own thread at score result, both for normal plays and courses.
	// This is called even with scores that wouldn't be sent to LR2IR or saved to the score.db, it's up to the module to
	// filter them.
	// For soft errors, SendScore should return SendScoreStatus::Retry. The game will retry calling a sensible amount
	// times with a backoff then.
	SendScoreStatus(OLR2_IR_API* SendScoreV1)(const IRScoreV1& score) = nullptr;
	// Forward compatibility, so you can try running IR modules designed for newer OpenLR2 versions.
	void* reserved1 = nullptr;
	void* reserved2 = nullptr;
	void* reserved3 = nullptr;
	void* reserved4 = nullptr;
	void* reserved5 = nullptr;
	void* reserved6 = nullptr;
};
