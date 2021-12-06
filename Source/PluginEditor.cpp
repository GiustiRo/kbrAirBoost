/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CtagdrcAudioProcessorEditor::CtagdrcAudioProcessorEditor(CtagdrcAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), processor(p), valueTreeState(vts), backgroundApp(Colour(Constants::Colors::bg_App)),
    inGainLSlider(this),
    makeupGainLSlider(this), treshLSlider(this), ratioLSlider(this), kneeLSlider(this), attackLSlider(this),
    releaseLSlider(this), mixLSlider(this), airLSlider(this)
      //powerButton("powerButton", DrawableButton::ButtonStyle::ImageOnButtonBackground)

{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setLookAndFeel(&scLaF);
    initWidgets();
    setSize(600, 200);
    startTimerHz(60);
    bg_image = ImageCache::getFromMemory(BinaryData::airBoost_bg_scratch_jpg, BinaryData::airBoost_bg_scratch_jpgSize);

}

CtagdrcAudioProcessorEditor::~CtagdrcAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void CtagdrcAudioProcessorEditor::paint(Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(backgroundApp);
    g.drawImage(bg_image, getLocalBounds().toFloat());
    //bg_image = Drawable::createFromImageData(BinaryData::power_white_svg, BinaryData::power_white_svgSize).get();
}

void CtagdrcAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(Constants::Margins::big);

    const auto headerHeight = area.getHeight() / 8;
    const auto footerHeight = area.getHeight() / 12;
    const auto btnAreaWidth = area.getWidth() / 3;
    const auto btnBotHeight = area.getHeight() / 5;

    auto header = area.removeFromTop(headerHeight).reduced(Constants::Margins::small);
    auto lBtnArea = area.removeFromLeft(btnAreaWidth).reduced(Constants::Margins::medium);
    auto rBtnArea = area.removeFromRight(btnAreaWidth).reduced(Constants::Margins::medium);
    auto botBtnArea = area.removeFromBottom(btnBotHeight).reduced(Constants::Margins::medium);
    auto footer = area.removeFromTop(footerHeight).reduced(Constants::Margins::small);


    const FlexItem::Margin knobMargin = FlexItem::Margin(Constants::Margins::medium);
    const FlexItem::Margin knobMarginSmall = FlexItem::Margin(Constants::Margins::medium);
    const FlexItem::Margin buttonMargin = FlexItem::Margin(Constants::Margins::small, Constants::Margins::small,
                                                           Constants::Margins::small,
                                                           Constants::Margins::small);
    FlexBox headerBox;
    headerBox.flexWrap = FlexBox::Wrap::noWrap;
    headerBox.flexDirection = FlexBox::Direction::row;
    headerBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    headerBox.items.add(FlexItem().withFlex(8.5).withMargin(buttonMargin));
    headerBox.items.add(FlexItem(/*appTitle*/).withFlex(6).withMargin(0));
    headerBox.items.add(FlexItem().withFlex(5).withMargin(buttonMargin));
    //headerBox.items.add(FlexItem(autoReleaseButton).withFlex(2).withMargin(buttonMargin));
    //headerBox.items.add(FlexItem(autoMakeupButton).withFlex(2).withMargin(buttonMargin));
    //headerBox.items.add(FlexItem(powerButton).withFlex(1).withMargin(buttonMargin));
    headerBox.performLayout(header.toFloat());

    FlexBox leftBtnBox;
    leftBtnBox.flexWrap = FlexBox::Wrap::noWrap;
    leftBtnBox.flexDirection = FlexBox::Direction::column;
    leftBtnBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    leftBtnBox.items.add(FlexItem().withFlex(1).withMargin(knobMarginSmall));
    leftBtnBox.items.add(FlexItem(mixLSlider).withFlex(3).withMargin(knobMarginSmall));
    leftBtnBox.items.add(FlexItem().withFlex(1).withMargin(knobMarginSmall));
    leftBtnBox.performLayout(lBtnArea.toFloat());

    FlexBox rightBtnBox;
    rightBtnBox.flexWrap = FlexBox::Wrap::noWrap;
    rightBtnBox.flexDirection = FlexBox::Direction::column;
    rightBtnBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    rightBtnBox.items.add(FlexItem().withFlex(1).withMargin(knobMarginSmall));
    rightBtnBox.items.add(FlexItem(airLSlider).withFlex(3).withMargin(knobMarginSmall));
    rightBtnBox.items.add(FlexItem().withFlex(1).withMargin(knobMarginSmall));
    rightBtnBox.performLayout(rBtnArea.toFloat());

    /*FlexBox botBtnBox;
    botBtnBox.flexWrap = FlexBox::Wrap::noWrap;
    botBtnBox.flexDirection = FlexBox::Direction::row;
    botBtnBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    botBtnBox.items.add(FlexItem(treshLSlider).withFlex(1).withMargin(knobMargin));
    botBtnBox.items.add(FlexItem(makeupGainLSlider).withFlex(1).withMargin(knobMargin));
    botBtnBox.performLayout(botBtnArea.toFloat());*/

    FlexBox footerBox;
    footerBox.flexWrap = FlexBox::Wrap::noWrap;
    footerBox.flexDirection = FlexBox::Direction::row;
    footerBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    /*botBtnBox.items.add(FlexItem(treshLSlider).withFlex(1).withMargin(knobMargin));
    botBtnBox.items.add(FlexItem(makeupGainLSlider).withFlex(1).withMargin(knobMargin));*/
    footerBox.performLayout(botBtnArea.toFloat());

    FlexBox meterBox;
    meterBox.flexWrap = FlexBox::Wrap::noWrap;
    meterBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    meterBox.items.add(FlexItem(meter).withFlex(1).withMargin(Constants::Margins::medium));
    meterBox.performLayout(area.toFloat());
}


void CtagdrcAudioProcessorEditor::buttonClicked(Button* b)
{
    //if (b == &autoAttackButton)attackLSlider.setEnabled(!attackLSlider.isEnabled());
    //if (b == &autoReleaseButton)releaseLSlider.setEnabled(!releaseLSlider.isEnabled());
    //if (b == &powerButton) setGUIState(powerButton.getToggleState());
}

void CtagdrcAudioProcessorEditor::timerCallback()
{
    int m = meter.getMode();
    switch (m)
    {
    case Meter::Mode::IN:
        meter.update(processor.currentInput.get());
        break;
    case Meter::Mode::OUT:
        meter.update(processor.currentOutput.get());
        break;
    case Meter::Mode::GR:
        meter.update(processor.gainReduction.get());
        break;
    default:
        break;
    }
}

void CtagdrcAudioProcessorEditor::initWidgets()
{
    /*addAndMakeVisible(inGainLSlider);
    inGainLSlider.reset(valueTreeState, "inputgain");
    inGainLSlider.setLabelText("Input");*/

    /*addAndMakeVisible(makeupGainLSlider);
    makeupGainLSlider.reset(valueTreeState, "makeup");
    makeupGainLSlider.setLabelText("Makeup");

    addAndMakeVisible(treshLSlider);
    treshLSlider.reset(valueTreeState, "threshold");
    treshLSlider.setLabelText("Threshold");

    addAndMakeVisible(ratioLSlider);
    ratioLSlider.reset(valueTreeState, "ratio");
    ratioLSlider.setLabelText("Ratio");*/

    /*addAndMakeVisible(kneeLSlider);
    kneeLSlider.reset(valueTreeState, "knee");
    kneeLSlider.setLabelText("Knee");*/

    /*addAndMakeVisible(attackLSlider);
    attackLSlider.reset(valueTreeState, "attack");
    attackLSlider.setLabelText("Attack");*/

    /*addAndMakeVisible(releaseLSlider);
    releaseLSlider.reset(valueTreeState, "release");
    releaseLSlider.setLabelText("Release");*/

    addAndMakeVisible(mixLSlider);
    mixLSlider.reset(valueTreeState, "mix");
    mixLSlider.setLabelText("Boost");

    addAndMakeVisible(airLSlider);
    airLSlider.reset(valueTreeState, "air");
    airLSlider.setLabelText("Air");

    addAndMakeVisible(appTitle);
    appTitle.setText("Kbr AirBoost", dontSendNotification);

    
    ////addAndMakeVisible(lahButton);
    //lahButton.setColour(TextButton::ColourIds::buttonColourId, Colour::fromRGB(245, 124, 0));
    //lahButton.setButtonText("LookAhead");
    //lahButton.setClickingTogglesState(true);
    //lahButton.setToggleState(false, dontSendNotification);
    //lahAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "lookahead", lahButton));

    //addAndMakeVisible(autoAttackButton);
    /*autoAttackButton.setColour(TextButton::ColourIds::buttonColourId, Colour::fromRGB(245, 124, 0));
    autoAttackButton.setButtonText("AutoAttack");
    autoAttackButton.setClickingTogglesState(true);
    autoAttackButton.setToggleState(false, dontSendNotification);
    autoAttackButton.addListener(this);
    autoAttackAttachment.reset(
        new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "autoattack", autoAttackButton));*/

    //addAndMakeVisible(autoReleaseButton);
    /*autoReleaseButton.setColour(TextButton::ColourIds::buttonColourId, Colour::fromRGB(245, 124, 0));
    autoReleaseButton.setButtonText("AutoRelease");
    autoReleaseButton.setClickingTogglesState(true);
    autoReleaseButton.setToggleState(false, dontSendNotification);
    autoReleaseButton.addListener(this);
    autoReleaseAttachment.reset(
        new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "autorelease", autoReleaseButton));

    addAndMakeVisible(autoMakeupButton);
    autoMakeupButton.setColour(TextButton::ColourIds::buttonColourId, Colour::fromRGB(245, 124, 0));
    autoMakeupButton.setButtonText("Makeup");
    autoMakeupButton.setClickingTogglesState(true);
    autoMakeupButton.setToggleState(false, dontSendNotification);
    autoMakeupButton.addListener(this);
    autoMakeupAttachment.reset(
        new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "automakeup", autoMakeupButton));*/

    /*addAndMakeVisible(powerButton);
    powerButton.setColour(TextButton::ColourIds::buttonColourId, Colour::fromRGB(245, 124, 0));
    powerButton.setImages(
        Drawable::createFromImageData(BinaryData::power_white_svg, BinaryData::power_white_svgSize).get());
    powerButton.setClickingTogglesState(true);
    powerButton.setToggleState(true, dontSendNotification);
    powerButton.addListener(this);
    powerAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "power", powerButton));*/

    addAndMakeVisible(meter);
    meter.setMode(Meter::Mode::OUT);

    
}

void CtagdrcAudioProcessorEditor::setGUIState(bool powerState)
{
    inGainLSlider.setEnabled(powerState);
    treshLSlider.setEnabled(powerState);
    ratioLSlider.setEnabled(powerState);
    kneeLSlider.setEnabled(powerState);
    makeupGainLSlider.setEnabled(powerState);
    mixLSlider.setEnabled(powerState);
    airLSlider.setEnabled(powerState);
    meter.setEnabled(powerState);
    meter.setGUIEnabled(powerState);
    /*lahButton.setEnabled(powerState);
    autoMakeupButton.setEnabled(powerState);

    autoAttackButton.setEnabled(powerState);
    autoReleaseButton.setEnabled(powerState);*/

    if (!powerState)
    {
        attackLSlider.setEnabled(powerState);
        releaseLSlider.setEnabled(powerState);
    }
    else
    {
        /*attackLSlider.setEnabled(!autoAttackButton.getToggleState());
        releaseLSlider.setEnabled(!autoReleaseButton.getToggleState());*/
    }
}
