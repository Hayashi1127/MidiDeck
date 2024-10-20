# include "WinRTMidi.hpp"

namespace WinRTMidi {

	std::wstring MidiIn::NoteOff(const MidiNoteOffMessage& message) {
		const uint8_t channel{ message.Channel() };
		const uint8_t note{ message.Note() };
		const uint8_t velocity{ message.Velocity() };
		std::wostringstream buff;
		buff << L"note off: channel " << channel
			<< L", note " << note
			<< L", velocity " << velocity;
		return buff.str();
	}

	std::wstring MidiIn::NoteOn(const MidiNoteOnMessage& message) {
		const uint8_t channel{ message.Channel() };
		const uint8_t note{ message.Note() };
		const uint8_t velocity{ message.Velocity() };
		std::wostringstream buff;
		buff << L"note on: channel " << channel
			<< L", note " << note
			<< L", velocity " << velocity;
		return buff.str();
	}

	std::wstring MidiIn::PolyphonicKeyPressure(const MidiPolyphonicKeyPressureMessage& message)
	{
		const uint8_t channel{ message.Channel() };
		const uint8_t note{ message.Note() };
		const uint8_t pressure{ message.Pressure() };
		std::wostringstream buff;
		buff << "polytouch: channel " << channel
			<< ", note " << note
			<< ", pressure " << pressure;
		return buff.str();
	}

	std::wstring MidiIn::ControlChange(const MidiControlChangeMessage& message)
	{
		const uint8_t channel{ message.Channel() };
		const uint8_t controller{ message.Controller() };
		const uint8_t controlValue{ message.ControlValue() };
		std::wostringstream buff;
		buff << L"control change: channel " << channel
			<< L", controller " << controller
			<< L", control value " << controlValue;
		return buff.str();
	}

	std::wstring MidiIn::ProgramChange(const MidiProgramChangeMessage& message)
	{
		const uint8_t channel{ message.Channel() };
		const uint8_t program{ message.Program() };
		std::wostringstream buff;
		buff << L"program change: channel " << channel
			<< L", program " << program;
		return buff.str();
	}

	std::wstring MidiIn::ChannelPressure(const MidiChannelPressureMessage& message)
	{
		const uint8_t channel{ message.Channel() };
		const uint8_t pressure{ message.Pressure() };
		std::wostringstream buff;
		buff << L"channel pressure: channel " << channel
			<< L", pressure " << pressure;
		return buff.str();
	}

	std::wstring MidiIn::PitchWheel(const MidiPitchBendChangeMessage& message)
	{
		const uint16_t channel{ message.Channel() };
		const uint16_t bend{ message.Bend() };
		std::wostringstream buff;
		buff << L"pitch wheel: channel " << channel
			<< L", bend " << bend;
		return buff.str();
	}

	std::wstring MidiIn::Sysex(const MidiSystemExclusiveMessage& message)
	{
		const IBuffer rawData{ message.RawData() };
		return L"sysex";
	}

	std::wstring MidiIn::TimeCode(const MidiTimeCodeMessage& message)
	{
		const uint8_t frameType{ message.FrameType() };
		const IBuffer rawData{ message.RawData() };
		std::wostringstream buff;
		buff << L"time code: frame type " << frameType;
		return buff.str();
	}

	std::wstring MidiIn::SongPositionPointer(const MidiSongPositionPointerMessage& message)
	{
		const uint16_t beats{ message.Beats() };
		const IBuffer raw_data{ message.RawData() };
		std::wostringstream buff;
		buff << L"songpos: beats " << beats;
		return buff.str();
	}

	std::wstring MidiIn::SongSelect(const MidiSongSelectMessage& message)
	{
		const uint8_t song{ message.Song() };
		const IBuffer raw_data{ message.RawData() };
		std::wostringstream buff;
		buff << L"song select: song " << song;
		return buff.str();
	}

	std::wstring MidiIn::TuneRequest(const MidiTuneRequestMessage& message)
	{
		return L"tune request";
	}

	std::wstring MidiIn::SystemExclusive(const MidiSystemExclusiveMessage& message)
	{
		return L"sysex eox";
	}

	std::wstring MidiIn::TimingClock(const MidiTimingClockMessage& message)
	{
		return L"clock";
	}

	std::wstring MidiIn::Start(const MidiStartMessage& message)
	{
		return L"clock";
	}

	std::wstring MidiIn::Continue(const MidiContinueMessage& message)
	{
		return L"continue";
	}

	std::wstring MidiIn::Stop(const MidiStopMessage& message)
	{
		return L"stop";
	}

	std::wstring MidiIn::ActiveSensing(const MidiActiveSensingMessage& message)
	{
		return L"active sensing";
	}

	std::wstring MidiIn::SystemReset(const MidiSystemResetMessage& message)
	{
		return L"system reset";
	}

	std::wstring MidiIn::MessageToStr(const IMidiMessage& message)
	{
		std::wostringstream buff;

		const auto t{ message.Type() };
		switch (t)
		{
		case MidiMessageType::NoteOff:
			buff << NoteOff(message.try_as<MidiNoteOffMessage>());
			break;
		case MidiMessageType::NoteOn:
			buff << NoteOn(message.try_as<MidiNoteOnMessage>());
			break;
		case MidiMessageType::PolyphonicKeyPressure:
			buff << PolyphonicKeyPressure(message.try_as<MidiPolyphonicKeyPressureMessage>());
			break;
		case MidiMessageType::ControlChange:
			buff << ControlChange(message.try_as<MidiControlChangeMessage>());
			break;
		case MidiMessageType::ProgramChange:
			buff << ProgramChange(message.try_as<MidiProgramChangeMessage>());
			break;
		case MidiMessageType::ChannelPressure:
			buff << ChannelPressure(
				message.try_as<MidiChannelPressureMessage>());
			break;
		case MidiMessageType::PitchBendChange:
			buff << PitchWheel(message.try_as<MidiPitchBendChangeMessage>());
			break;
		case MidiMessageType::SystemExclusive:
			buff << Sysex(message.try_as<MidiSystemExclusiveMessage>());
			break;
		case MidiMessageType::MidiTimeCode:
			buff << TimeCode(message.try_as<MidiTimeCodeMessage>());
			break;
		case MidiMessageType::SongPositionPointer:
			buff << SongPositionPointer(message.try_as<MidiSongPositionPointerMessage>());
			break;
		case MidiMessageType::SongSelect:
			buff << SongSelect(message.try_as<MidiSongSelectMessage>());
			break;
		case MidiMessageType::TuneRequest:
			buff << TuneRequest(message.try_as<MidiTuneRequestMessage>());
			break;
		case MidiMessageType::EndSystemExclusive:
			buff << SystemExclusive(message.try_as<MidiSystemExclusiveMessage>());
			break;
		case MidiMessageType::TimingClock:
			buff << TimingClock(message.try_as<MidiTimingClockMessage>());
			break;
		case MidiMessageType::Start:
			buff << Start(message.try_as<MidiStartMessage>());
			break;
		case MidiMessageType::Continue:
			buff << Continue(message.try_as<MidiContinueMessage>());
			break;
		case MidiMessageType::Stop:
			buff << Stop(message.try_as<MidiStopMessage>());
			break;
		case MidiMessageType::ActiveSensing:
			buff << ActiveSensing(message.try_as<MidiActiveSensingMessage>());
			break;
		case MidiMessageType::SystemReset:
			buff << SystemReset(message.try_as<MidiSystemResetMessage>());
			break;
		default:
			buff << L"unknown ("
				<< static_cast<int>(t)
				<< L")";
		}

		const IBuffer raw_data = message.RawData();
		const std::basic_string_view<uint8_t> raw_data_sv{ raw_data.data(), raw_data.Length() };
		buff << "," << std::hex;
		for (auto u : raw_data_sv)
		{
			buff << " "
				<< std::setw(2) << std::setfill(L'0')
				<< u;
		}

		return buff.str();
	}

	winrt::fire_and_forget MidiIn::ShowMidiMessage(IMidiMessage message)
	{
		co_await winrt::resume_background();
		const auto timestamp = message.Timestamp();
		const std::chrono::nanoseconds duration = timestamp;
		{
			// メッセージ作成、表示中はmutexで一旦ブロック
			std::lock_guard<std::mutex> lock(mtxShowMessage);
			std::wcout
				<< duration.count()
				<< L", "
				<< MessageToStr(message)
				<< std::endl;
		}
	}

	void MidiIn::MidiInCallback(const MidiInPort& sender, const MidiMessageReceivedEventArgs& e)
	{
		const auto message = e.Message();
		ShowMidiMessage(message);

		if (message.Type() == MidiMessageType::NoteOn)
		{
			MidiNoteOnMessage m = message.try_as<MidiNoteOnMessage>();
			midiCallbackFunc(m.Note());
		}
	}

	void MidiIn::SetCallbackFunc(void (*Func)(byte))
	{
		midiCallbackFunc = Func;
	}

	MidiIn::MidiIn()
	{
		std::lock_guard<std::mutex> lock(mtx);
	}

	MidiIn::~MidiIn()
	{
		// この後の this ポインタ参照を防ぐ。
		inDevice.MessageReceived(before_token);
		inDevice.Close();
	}

	IAsyncAction MidiIn::ListMidiDevices(winrt::hstring deviceSelector)
	{
		const DeviceInformationCollection devs = co_await DeviceInformation::FindAllAsync(deviceSelector);
		if (midiInPorts.size() != 0)
		{
			midiInPorts.clear();
		}

		for (const auto& d : devs)
		{
			WinRTMidi::MidiDevice device;
			device.name = d.Name();
			device.id = d.Id();
			device.display_name = d.Name();

			// ID の 16 進数 8 桁部分を抽出する
			std::wsmatch m;
			if (regex_search(device.id, m, hexIdPattern))
			{
				device.hex_id = m[1];
				std::wostringstream ss;
				ss << device.name
					<< L" [ "
					<< device.id
					<< L" ]";
				device.display_name = ss.str();
			}

			midiInPorts.push_back(device);
		}
	}

	IAsyncOperation<MidiInPort> MidiIn::SelectMidiInDevice()
	{
		co_await ListMidiDevices(MidiInPort::GetDeviceSelector());

		// MIDI IN ポートの選択肢を表示
		std::wcout
			<< std::endl
			<< L"MIDI IN ports"
			<< std::endl << std::endl;

		for (unsigned int i = 0; i < midiInPorts.size(); i++)
		{
			std::wcout
				<< i
				<< L": "
				<< midiInPorts[i].display_name
				<< std::endl;
		}

		// コンソールから選択肢を入力
		std::wcout
			<< std::endl
			<< L"Select number > "
			<< std::flush;

		unsigned int choice;
		std::wcin >> choice;

		if (choice < midiInPorts.size())
		{
			// 選択されたポートの情報を表示
			std::wcout
				<< std::endl
				<< L"Selected: "
				<< choice
				<< L", "
				<< midiInPorts[choice].name
				<< L", "
				<< midiInPorts[choice].id
				<< L", "
				<< midiInPorts[choice].hex_id
				<< L", "
				<< midiInPorts[choice].display_name
				<< std::endl;

			// ポートの作成を要求
			IAsyncOperation<MidiInPort> aysncGetPort = MidiInPort::FromIdAsync(midiInPorts[choice].id);

			// 5 秒待って完了していたら結果を受け取って返す
			if (aysncGetPort.wait_for(5s) == AsyncStatus::Completed) {
				std::wcout
					<< L"Success Opening your selected Device's Port."
					<< std::endl;
				co_return aysncGetPort.GetResults();
			}

			std::wcout
				<< L"Timeout"
				<< std::endl;
			co_return nullptr;
		}
		else
		{
			// 選択範囲外
			std::wcout
				<< L"Error. Please Select Correct Number.\n"
				<< L"Your choice is: "
				<< choice
				<< L"\n"
				<< L"However, you have "
				<< midiInPorts.size()
				<< L"devices."
				<< std::endl;
			co_return nullptr;
		}
	}

	IAsyncAction MidiIn::Start()
	{
		inDevice = co_await SelectMidiInDevice();

		if (!inDevice)
		{
			std::wcout
				<< L"Error: MIDI IN is not opened"
				<< std::endl;
			co_return;
		}

		std::wcout
			<< L"Callback starting..."
			<< std::endl;

		// MIDI メッセージ受信時のイベントハンドラを設定し、
		// 元のイベントハンドラのトークンを保存する。
		// this ポインタを使っているのでインスタンス破棄中などの
		// 微妙なタイミングでイベント発生するとマズいことになる。
		// get_strong() で強参照を得るなどした方がよさそうではあるが、
		// 本クラスは C++/WinRT のクラスから派生していないので使えない。
		before_token = inDevice.MessageReceived({ this, &MidiIn::MidiInCallback });

		std::wcout
			<< L"Started"
			<< std::endl;
	}
};
