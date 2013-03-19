/*
 *	PlatformInterface.h
 *
 *	Defines an interface for IO controllers (eg. Key Largo)
 *
 *  Created by Aram Lindahl on Mon Mar 10 2003.
 *  Copyright (c) 2003 AppleComputer. All rights reserved.
 */
#ifndef __PLATFORMINTERFACE__
#define	__PLATFORMINTERFACE__
 
#include <IOKit/IOService.h>
#include <IOKit/IOInterruptEventSource.h>
#include "AudioHardwareConstants.h"
#include <IOKit/ppc/IODBDMA.h>

typedef enum {
	kI2C_StandardMode 			= 0,
	kI2C_StandardSubMode		= 1,
	kI2C_CombinedMode			= 2
} BusMode;

typedef enum {
	kI2S_18MHz 					= 0,
	kI2S_45MHz					= 1,
	kI2S_49MHz					= 2
} I2SClockFrequency;

//	If this enumeration changes then please apply the same changes to the DiagnosticSupport sources.
typedef enum GpioAttributes {
	kGPIO_Disconnected			= 0,
	kGPIO_Connected,
	kGPIO_Unknown,
	kGPIO_Muted,
	kGPIO_Unmuted,
	kGPIO_Reset,
	kGPIO_Run,
	kGPIO_MuxSelectDefault,
	kGPIO_MuxSelectAlternate,
	kGPIO_CodecInterruptActive,
	kGPIO_CodecInterruptInactive,
	kGPIO_CodecIRQEnable,
	kGPIO_CodecIRQDisable,
	kGPIO_TypeIsAnalog,
	kGPIO_TypeIsDigital
};

//	If this enumeration changes then please apply the same changes to the DiagnosticSupport sources.
typedef enum GPIOSelector {
	kGPIO_Selector_AnalogCodecReset	= 0,
	kGPIO_Selector_ClockMux,
	kGPIO_Selector_CodecInterrupt,
	kGPIO_Selector_CodecErrorInterrupt,
	kGPIO_Selector_ComboInJackType,
	kGPIO_Selector_ComboOutJackType,
	kGPIO_Selector_DigitalCodecReset,
	kGPIO_Selector_DigitalInDetect,
	kGPIO_Selector_DigitalOutDetect,
	kGPIO_Selector_HeadphoneDetect,
	kGPIO_Selector_HeadphoneMute,
	kGPIO_Selector_InputDataMux,
	kGPIO_Selector_InternalSpeakerID,
	kGPIO_Selector_LineInDetect,
	kGPIO_Selector_LineOutDetect,
	kGPIO_Selector_LineOutMute,
	kGPIO_Selector_SpeakerDetect,
	kGPIO_Selector_SpeakerMute
};

//	If this enumeration changes then please apply the same changes to the DiagnosticSupport sources.
typedef enum GPIOType {
	kGPIO_Type_ConnectorType = 0,
	kGPIO_Type_Detect,
	kGPIO_Type_Irq,
	kGPIO_Type_MuteL,
	kGPIO_Type_MuteH,
	kGPIO_Type_Mux,
	kGPIO_Type_Reset,
};

//	If this enumeration changes then please apply the same changes to the DiagnosticSupport sources.
typedef enum {
	kCODEC_RESET_Analog			= 0,
	kCODEC_RESET_Digital
} CODEC_RESET;

//	If this enumeration changes then please apply the same changes to the DiagnosticSupport sources.
typedef enum {
	kUnknownInterrupt			= 0,
	kCodecErrorInterrupt,
	kCodecInterrupt,
	kDigitalInDetectInterrupt,
	kDigitalOutDetectInterrupt,
	kHeadphoneDetectInterrupt,
	kLineInputDetectInterrupt,
	kLineOutputDetectInterrupt,
	kSpeakerDetectInterrupt
} PlatformInterruptSource;

//	If this enumeration changes then please apply the same changes to the DiagnosticSupport sources.
typedef enum PlatformInterfaceObjectType {
	kPlatformInterfaceType_Unknown			=	0,
	kPlatformInterfaceType_KeyLargo,
	kPlatformInterfaceType_K2,
	kPlatformInterfaceType_Shasta
} ;

//	If this structure changes then please apply the same changes to the DiagnosticSupport sources.
typedef struct { 
	UInt32					intCtrl;
	UInt32					serialFmt;
	UInt32					codecMsgOut;
	UInt32					codecMsgIn;
	UInt32					frameCount;
	UInt32					frameCountToMatch;
	UInt32					dataWordSizes;
	UInt32					peakLevelSfSel;
	UInt32					peakLevelIn0;
	UInt32					peakLevelIn1;
	UInt32					reserved_11;
	UInt32					reserved_12;
	UInt32					reserved_13;
	UInt32					reserved_14;
	UInt32					reserved_15;
	UInt32					reserved_16;
	UInt32					reserved_17;
	UInt32					reserved_18;
	UInt32					reserved_19;
	UInt32					reserved_20;
	UInt32					reserved_21;
	UInt32					reserved_22;
	UInt32					reserved_23;
	UInt32					reserved_24;
	UInt32					reserved_25;
	UInt32					reserved_26;
	UInt32					reserved_27;
	UInt32					reserved_28;
	UInt32					reserved_29;
	UInt32					reserved_30;
	UInt32					reserved_31;
} i2sDescriptor ;
typedef i2sDescriptor * i2sDescriptorPtr;

//	If this structure changes then please apply the same changes to the DiagnosticSupport sources.
typedef struct {
	UInt32					i2sEnable;
	UInt32					i2sClockEnable;
	UInt32					i2sReset;
	UInt32					i2sCellEnable;
	UInt32					clock18mHzEnable;
	UInt32					clock45mHzEnable;
	UInt32					clock49mHzEnable;
	UInt32					pll45mHzShutdown;
	UInt32					pll49mHzShutdown;
	UInt32					reserved_10;
	UInt32					reserved_11;
	UInt32					reserved_12;
	UInt32					reserved_13;
	UInt32					reserved_14;
	UInt32					reserved_15;
	UInt32					reserved_16;
	UInt32					reserved_17;
	UInt32					reserved_18;
	UInt32					reserved_19;
	UInt32					reserved_20;
	UInt32					reserved_21;
	UInt32					reserved_22;
	UInt32					reserved_23;
	UInt32					reserved_24;
	UInt32					reserved_25;
	UInt32					reserved_26;
	UInt32					reserved_27;
	UInt32					reserved_28;
	UInt32					reserved_29;
	UInt32					reserved_30;
	UInt32					reserved_31;
} fcrDescriptor ;
typedef fcrDescriptor * fcrDescriptorPtr ;

//	If this structure changes then please apply the same changes to the DiagnosticSupport sources.
typedef struct {
	GpioAttributes			gpio_AnalogCodecReset;
	GpioAttributes			gpio_ClockMux;
	GpioAttributes			gpio_CodecInterrupt;
	GpioAttributes			gpio_CodecErrorInterrupt;
	GpioAttributes			gpio_ComboInJackType;
	GpioAttributes			gpio_ComboOutJackType;
	GpioAttributes			gpio_DigitalCodecReset;
	GpioAttributes			gpio_DigitalInDetect;
	GpioAttributes			gpio_DigitalOutDetect;
	GpioAttributes			gpio_HeadphoneDetect;
	GpioAttributes			gpio_HeadphoneMute;
	GpioAttributes			gpio_InputDataMux;
	GpioAttributes			gpio_LineInDetect;
	GpioAttributes			gpio_LineOutDetect;
	GpioAttributes			gpio_LineOutMute;
	GpioAttributes			gpio_SpeakerDetect;
	GpioAttributes			gpio_SpeakerMute;
	GpioAttributes			gpio_InternalSpeakerID;
	GpioAttributes			reserved_18;
	GpioAttributes			reserved_19;
	GpioAttributes			reserved_20;
	GpioAttributes			reserved_21;
	GpioAttributes			reserved_22;
	GpioAttributes			reserved_23;
	GpioAttributes			reserved_24;
	GpioAttributes			reserved_25;
	GpioAttributes			reserved_26;
	GpioAttributes			reserved_27;
	GpioAttributes			reserved_28;
	GpioAttributes			reserved_29;
	GpioAttributes			reserved_30;
	GpioAttributes			reserved_31;
} gpioDescriptor;
typedef gpioDescriptor * gpioDescriptorPtr;

typedef struct {
	UInt32					i2c_pollingMode;
	UInt32					i2c_errorStatus;
	UInt32					reserved_02;
	UInt32					reserved_03;
	UInt32					reserved_04;
	UInt32					reserved_05;
	UInt32					reserved_06;
	UInt32					reserved_07;
	UInt32					reserved_08;
	UInt32					reserved_09;
	UInt32					reserved_0A;
	UInt32					reserved_0B;
	UInt32					reserved_0C;
	UInt32					reserved_0D;
	UInt32					reserved_1E;
	UInt32					reserved_1F;
} i2cDescriptor;
typedef i2cDescriptor * i2cDescriptorPtr;

//	If this structure changes then please apply the same changes to the DiagnosticSupport sources.
typedef struct {
	PlatformInterfaceObjectType				platformType;
	fcrDescriptor							fcr;
	i2sDescriptor							i2s;
	gpioDescriptor							gpio;
	i2cDescriptor							i2c;
} PlatformStateStruct ;
typedef PlatformStateStruct * PlatformStateStructPtr;

#define kAnalogCodecResetSel kCodecResetSel

class AppleOnboardAudio;
class AppleOnboardAudioUserClient;

class PlatformInterface : public OSObject {

    OSDeclareDefaultStructors(PlatformInterface);

public:	

	virtual bool			init(IOService* device, AppleOnboardAudio* provider, UInt32 inDBDMADeviceIndex);
	virtual void			free (void);
	virtual bool			registerInterrupts ( IOService * device );
	virtual void			poll ( void ) { return; }
	
	virtual	void			setWorkLoop(IOWorkLoop* inWorkLoop) {return;}					
	//
	// Codec Methods
	//
	virtual bool			readCodecRegister(UInt8 address, UInt8 subAddress, UInt8 *data, UInt16 len, BusMode mode) {return false;}
	virtual bool			writeCodecRegister(UInt8 address, UInt8 subAddress, UInt8 *data, UInt16 len, BusMode mode) {return false;}

	virtual IOReturn		setCodecReset ( CODEC_RESET target, GpioAttributes reset ) { return kIOReturnError; }
	virtual GpioAttributes	getCodecReset ( CODEC_RESET target ) { return kGPIO_Unknown; }
	//
	// I2S Methods: FCR3
	//
	virtual IOReturn		requestI2SClockSource(I2SClockFrequency inFrequency) {return kIOReturnError;}
	virtual IOReturn		releaseI2SClockSource(I2SClockFrequency inFrequency) {return kIOReturnError;}
	//
	// I2S Methods: FCR1
	//
	virtual IOReturn		setI2SEnable(bool enable) {return kIOReturnError;}
	virtual bool			getI2SEnable() {return false;}

	virtual IOReturn		setI2SClockEnable(bool enable) {return kIOReturnError;}
	virtual bool			getI2SClockEnable() {return false;}

	virtual IOReturn		setI2SCellEnable(bool enable) {return kIOReturnError;}
	virtual bool			getI2SCellEnable() {return false;}
	
	virtual IOReturn		setI2SSWReset(bool enable) {return kIOReturnError;}
	virtual bool			getI2SSWReset() {return false;}
	//
	// I2S Methods: IOM Control
	//
	virtual IOReturn		setSerialFormatRegister(UInt32 serialFormat) {return kIOReturnError;}
	virtual UInt32			getSerialFormatRegister() {return 0;}

	virtual IOReturn		setDataWordSizes(UInt32 dataWordSizes) {return kIOReturnError;}
	virtual UInt32			getDataWordSizes() {return 0;}
	
	virtual IOReturn		setFrameCount(UInt32 value) {return kIOReturnError;}
	virtual UInt32			getFrameCount() {return 0;}

	virtual IOReturn		setI2SIOMIntControl(UInt32 intCntrl) {return kIOReturnError;}
	virtual UInt32			getI2SIOMIntControl() {return 0;}
	//
	// GPIO Methods
	//
	virtual IOReturn		setClockMux(GpioAttributes muxState) { return kIOReturnError; }
	virtual GpioAttributes	getClockMux() { return kGPIO_Unknown; }

	virtual GpioAttributes	getCodecErrorInterrupt() {return kGPIO_Unknown;}

	virtual GpioAttributes	getCodecInterrupt() {return kGPIO_Unknown;}

	virtual	GpioAttributes	getComboInJackTypeConnected() {return kGPIO_Unknown;}			//	for combo digital/analog connector
	virtual	GpioAttributes	getComboOutJackTypeConnected() {return kGPIO_Unknown;}		//	for combo digital/analog connector

	virtual	GpioAttributes	getDigitalInConnected() {return kGPIO_Unknown;}
	virtual	GpioAttributes	getDigitalOutConnected() {return kGPIO_Unknown;}

	virtual GpioAttributes	getHeadphoneConnected() {return kGPIO_Unknown;}

	virtual IOReturn 		setHeadphoneMuteState( GpioAttributes muteState ) {return kIOReturnError;}
	virtual GpioAttributes 	getHeadphoneMuteState() {return kGPIO_Unknown;}
	
	virtual IOReturn		setInputDataMux(GpioAttributes muxState) { return kIOReturnError; }
	virtual GpioAttributes	getInputDataMux() { return kGPIO_Unknown; }

	virtual GpioAttributes	 getInternalSpeakerID() {return kGPIO_Unknown;}

	virtual	GpioAttributes	getLineOutConnected() {return kGPIO_Unknown;}
	virtual	GpioAttributes	getLineInConnected() {return kGPIO_Unknown;}

	virtual IOReturn 		setLineOutMuteState( GpioAttributes muteState ) {return kIOReturnError;}
	virtual GpioAttributes 	getLineOutMuteState() {return kGPIO_Unknown;}
	
	virtual GpioAttributes	getSpeakerConnected() {return kGPIO_Unknown;}

	virtual IOReturn 		setSpeakerMuteState( GpioAttributes muteState ) {return kIOReturnError;}
	virtual GpioAttributes 	getSpeakerMuteState() {return kGPIO_Unknown;}
	
	static void				headphoneDetectInterruptHandler ( OSObject *owner, IOInterruptEventSource *source, UInt32 count, void * arg4 );
	static void				speakerDetectInterruptHandler ( OSObject *owner, IOInterruptEventSource *source, UInt32 count, void * arg4 );
	static void				lineInDetectInterruptHandler ( OSObject *owner, IOInterruptEventSource *source, UInt32 count, void * arg4 );
	static void				lineOutDetectInterruptHandler ( OSObject *owner, IOInterruptEventSource *source, UInt32 count, void * arg4 );
	static void				digitalInDetectInterruptHandler ( OSObject *owner, IOInterruptEventSource *source, UInt32 count, void * arg4 );
	static void				digitalOutDetectInterruptHandler ( OSObject *owner, IOInterruptEventSource *source, UInt32 count, void * arg4 );
	static void				codecInterruptHandler ( OSObject *owner, IOInterruptEventSource *source, UInt32 count, void * arg4 );
	static void				codecErrorInterruptHandler ( OSObject *owner, IOInterruptEventSource *source, UInt32 count, void * arg4 );

	virtual  void 			logFCR1() {return;}
	virtual  void 			logFCR3() {return;}

	//
	// Set Interrupt Handler Methods
	//
	virtual	IOReturn		disableInterrupt ( PlatformInterruptSource source ) { return kIOReturnError; }
	virtual	IOReturn		enableInterrupt ( PlatformInterruptSource source ) { return kIOReturnError; }
	virtual	IOReturn		registerInterruptHandler (IOService * theDevice, void * interruptHandler, PlatformInterruptSource source ) { return kIOReturnError; }
	virtual	IOReturn		unregisterInterruptHandler (IOService * theDevice, void * interruptHandler, PlatformInterruptSource source ) { return kIOReturnError; }

	//
	// DBDMA Memory Address Acquisition Methods
	//
	virtual	IODBDMAChannelRegisters *	GetInputChannelRegistersVirtualAddress ( IOService * dbdmaProvider ) { return NULL; }
	virtual	IODBDMAChannelRegisters *	GetOutputChannelRegistersVirtualAddress ( IOService * dbdmaProvider ) { return NULL; }
	virtual void						LogDBDMAChannelRegisters ( void );

	//	
	//	User Client Support
	//
	virtual IOReturn		getPlatformState ( PlatformStateStructPtr outState ) { return kIOReturnError; }
	virtual IOReturn		setPlatformState ( PlatformStateStructPtr inState ) { return kIOReturnError; }
	
	virtual void			LogFCR ( void ) { return; }
	virtual void			LogI2S ( void ) { return; }
	virtual void			LogGPIO ( void ) { return; }
	virtual void			LogInterruptGPIO ( void ) { return; }
protected:

	AppleOnboardAudio *		mProvider;

	bool					mIsComboInJack;
	bool					mIsComboOutJack;
	GpioAttributes			mComboInJackState;
	GpioAttributes			mComboOutJackState;
};

#endif	/*	__PLATFORMINTERFACE__	*/