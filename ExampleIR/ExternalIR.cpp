#include <LR2_customir_api.h>

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <print>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

namespace State {
    static std::filesystem::path path;
    static int scoresSaved = 0;
}

static const char* GetName() {
    std::println(std::cout, "GetName");
    return "ExampleIR";
}

static bool Login() {
    std::println(std::cout, "Login");
    return true;
}

static SendScoreStatus SendScore(const IRScoreV1& score) {
    std::println(std::cout, "SendScore({{.song.hash={}}})", score.song.hash);
    constexpr const char* lamps[6] = { "NO PLAY", "FAIL", "EASY", "NORMAL", "HARD", "FULL COMBO" };
    if (score.settings.assist[score.state.player]) return SendScoreStatus::Fail;
    std::string filename = std::format("score{}.txt", State::scoresSaved);
    State::scoresSaved++;
    std::string processedScore = std::format(
        "md5: {}\n"
        "keymode: {}\n"
        "exscore: {}\n"
        "pgreat: {}\n"
        "great: {}\n"
        "good: {}\n"
        "bad: {}\n"
        "poor: {}\n"
        "fast: {}\n"
        "slow: {}\n"
        "cb: {}\n"
        "lamp: {}\n",
        score.song.hash, score.state.keymode, score.exscore,
        score.judgements_total.epg + score.judgements_total.lpg,
        score.judgements_total.egr + score.judgements_total.lgr,
        score.judgements_total.egd + score.judgements_total.lgd,
        score.judgements_total.ebd + score.judgements_total.lbd,
        score.judgements_total.epr + score.judgements_total.lpr,
        score.judgements_total.fast, score.judgements_total.slow, score.judgements_total.cb,
        lamps[score.clearType]
    );
    std::ofstream dump(State::path / filename);
    dump << processedScore;
    return SendScoreStatus::Ok;
}

extern "C" OLR2_IR_EXPORT void GetMethodTable(MethodTable& table) {
    // Fill out the pointers to methods you want to use. Leave them at nullptr if you don't want to use them.
    // As API gets updated, new methods may appear available at MethodTable, but old ones will never be removed or their
    // prototypes modified, so method indexes are stable.
    table.GetName = &GetName;
    table.LoginV1 = &Login;
    table.SendScoreV1 = &SendScore;
}

#ifdef _WIN32
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    wchar_t modulePath[MAX_PATH]{};
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Get path to the folder the .dll is running from.
        // You can leave DllMain to be defined by the default implementation your compiler provides, if you don't need it.
        // Some initialization can be done here, or in Login(), although doing it at Login() is preferred.
        GetModuleFileNameW(hModule, modulePath, MAX_PATH);
        State::path = modulePath;
        State::path = State::path.parent_path();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#endif // _WIN32
