# include "./src/Mylibs.hpp"

/// <summary>
/// ID の 16 進数 8 桁部分を抽出するパターンの実体
/// </summary>
const std::wregex WinRTMidi::MidiIn::hexIdPattern{ std::wregex(L"#MIDII_([0-9A-F]{8})\\..+#") };

/// <summary>
/// コンストラクタのスレッド間競合を防ぐmutexの実体
/// </summary>
std::mutex WinRTMidi::MidiIn::mtx;

/// <summary>
/// メッセージ表示中にスレッド間の割込みを防ぐmutexの実体
/// </summary>
std::mutex WinRTMidi::MidiIn::mtxShowMessage;

/// <summary>
/// Midiイベントから呼び出したいコールバック
/// </summary>
/// <param name="note"></param>
void midiFunc(byte note)
{
	// Midiコンの各メッセージと呼び出したい処理を書く
	// 適宜書き換えて使ってください
	switch (note)
	{
		case 36:
			system("notepad.exe");
			break;
		case 38:
			system("start Chrome.exe");
			break;
		case 50:
			system("calc.exe");
			break;
	}
}

int main()
{
	// Midi初期化
	init_apartment();
	WinRTMidi::MidiIn midiIn;
	midiIn.SetCallbackFunc(midiFunc);
	midiIn.Start().get();

	while(1)
	{

	}
}
