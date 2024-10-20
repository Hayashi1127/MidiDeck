# pragma once
# include <iostream>
# include <chrono>
# include <future>
# include <mutex>
# include <iomanip>
# include <regex>
# include <sstream>
# include <string>
# include <string_view>
# include <vector>

# include <windows.h>

# include <winrt/base.h>
# include <winrt/Windows.Foundation.h>
# include <winrt/Windows.Foundation.collections.h>
# include <winrt/Windows.Devices.Enumeration.h>
# include <winrt/Windows.Devices.Midi.h>
# include <winrt/Windows.Storage.Streams.h>

using namespace std::chrono_literals;
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Devices::Midi;
using namespace Windows::Storage::Streams;

namespace WinRTMidi {
	/// <summary>
	/// Midiデバイス構造体
	/// </summary>
	struct MidiDevice {
		/// <summary>
		/// デバイスの名前
		/// </summary>
		std::wstring name;

		/// <summary>
		/// MidiID
		/// </summary>
		std::wstring id;

		/// <summary>
		/// MidiIDの16進数下8桁
		/// </summary>
		std::wstring hex_id;

		/// <summary>
		/// Midiデバイスの表示名
		/// </summary>
		std::wstring display_name;
	};

	/// <summary>
	/// MidiInput用クラス
	/// </summary>
	class MidiIn {
	private:
		/// <summary>
		/// MidiIDの16進数8桁部分抽出用のパターン
		/// </summary>
		static const std::wregex hexIdPattern;

		/// <summary>
		/// コンストラクタのスレッド間競合を防ぐためのmutex
		/// </summary>
		static std::mutex mtx;

		/// <summary>
		/// メッセージ表示中にスレッド間の割込みを防ぐ mutex
		/// </summary>
		static std::mutex mtxShowMessage;

		/// <summary>
		/// 終了要求を示すイベント
		/// </summary>
		// static winrt::handle interruptEventHandle;

		/// <summary>
		/// MidiInデバイス
		/// </summary>
		MidiInPort inDevice = nullptr;

		/// <summary>
		/// MIDI メッセージ受信時のイベントハンドラを設定し、元のイベントハンドラのトークンを保存する
		/// </summary>
		winrt::event_token before_token;

		/// <summary>
		/// 使用可能なMidiInデバイスのリスト
		/// </summary>
		std::vector<MidiDevice> midiInPorts;

		/// <summary>
		/// Midiコールバックで呼び出す関数のポインタ
		/// </summary>
		/// <param name="message"></param>
		void (*midiCallbackFunc)(byte);

		std::wstring NoteOff(const MidiNoteOffMessage& message);

		std::wstring NoteOn(const MidiNoteOnMessage& message);

		std::wstring PolyphonicKeyPressure(const MidiPolyphonicKeyPressureMessage& message);

		std::wstring ControlChange(const MidiControlChangeMessage& message);

		std::wstring ProgramChange(const MidiProgramChangeMessage& message);

		std::wstring ChannelPressure(const MidiChannelPressureMessage& message);

		std::wstring PitchWheel(const MidiPitchBendChangeMessage& message);

		std::wstring Sysex(const MidiSystemExclusiveMessage& message);

		std::wstring TimeCode(const MidiTimeCodeMessage& message);

		std::wstring SongPositionPointer(const MidiSongPositionPointerMessage& message);

		std::wstring SongSelect(const MidiSongSelectMessage& message);

		std::wstring TuneRequest(const MidiTuneRequestMessage& message);

		std::wstring SystemExclusive(const MidiSystemExclusiveMessage& message);

		std::wstring TimingClock(const MidiTimingClockMessage& message);

		std::wstring Start(const MidiStartMessage& message);

		std::wstring Continue(const MidiContinueMessage& message);

		std::wstring Stop(const MidiStopMessage& message);

		std::wstring ActiveSensing(const MidiActiveSensingMessage& message);

		std::wstring SystemReset(const MidiSystemResetMessage& message);

		/// <summary>
		/// Midiメッセージを文字列に変換
		/// </summary>
		/// <param name="message">Midiメッセージ</param>
		/// <returns>Midiメッセージを文字列化したもの</returns>
		std::wstring MessageToStr(const IMidiMessage& message);

		/// <summary>
		/// MidiMessageを表示する
		/// この関数はコルーチンであり、呼び出し直後にco_awaitしてバックグラウンドで再開する
		/// </summary>
		/// <param name="message">MidiMessage</param>
		/// <returns></returns>
		winrt::fire_and_forget ShowMidiMessage(IMidiMessage message);

		/// <summary>
		/// MidiInイベントで呼ばれるコールバック
		/// </summary>
		/// <param name="sender">イベントが発生したMidiInポート</param>
		/// <param name="e">Midiメッセージ情報</param>
		void MidiInCallback(const MidiInPort& sender, const MidiMessageReceivedEventArgs& e);

		/// <summary>
		/// Ctrl + Cなどが押された時のイベントハンドラ
		/// </summary>
		/// <param name="dwCtrlType"></param>
		/// <returns></returns>
		static BOOL WINAPI HandlerRoutine(DWORD dwCtrlType);

	public:
		MidiIn();

		~MidiIn();

		/// <summary>
		/// 使用可能なMidiデバイスのリストを取得する
		/// </summary>
		/// <param name="deviceSelector">MidiInPort::GetDeviceSelector()またはMidiOutPort::GetDeviceSelector</param>
		/// <returns>Midiデバイスのリスト</returns>
		IAsyncAction ListMidiDevices(winrt::hstring deviceSelector);

		/// <summary>
		/// MidiInデバイスを選択する
		/// </summary>
		/// <returns>選択されたMidiInデバイス</returns>
		IAsyncOperation<MidiInPort> SelectMidiInDevice();

		/// <summary>
		/// MidiInデバイスによるMidi信号の受付を開始する
		/// </summary>
		/// <returns></returns>
		IAsyncAction Start();

		void SetCallbackFunc(void (*Func)(byte));
	};
}
