<GameFile>
  <PropertyGroup Name="GameOverScene" Type="Scene" ID="afa1cd2f-9b89-4576-a505-e0aec29059fc" Version="2.3.3.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" Tag="11" ctype="GameNodeObjectData">
        <Size X="640.0000" Y="960.0000" />
        <Children>
          <AbstractNodeData Name="gameover_1" ActionTag="-996224896" Tag="12" IconVisible="False" LeftMargin="2.6708" RightMargin="157.3292" TopMargin="109.5501" BottomMargin="-1.5501" ctype="SpriteObjectData">
            <Size X="480.0000" Y="852.0000" />
            <AnchorPoint />
            <Position X="2.6708" Y="-1.5501" />
            <Scale ScaleX="1.3264" ScaleY="1.1233" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0042" Y="-0.0016" />
            <PreSize X="0.7500" Y="0.8875" />
            <FileData Type="PlistSubImage" Path="gameover.png" Plist="assets/ui/shoot_background.plist" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="PointCode" ActionTag="-258727849" Tag="13" IconVisible="False" LeftMargin="285.8395" RightMargin="342.1605" TopMargin="530.4282" BottomMargin="403.5718" LabelText="Fnt Text Label" ctype="TextBMFontObjectData">
            <Size X="12.0000" Y="26.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="291.8395" Y="416.5718" />
            <Scale ScaleX="2.5365" ScaleY="4.3802" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4560" Y="0.4339" />
            <PreSize X="0.0188" Y="0.0271" />
            <LabelBMFontFile_CNB Type="Normal" Path="assets/font/font.fnt" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Button_1" ActionTag="-45874677" Tag="16" IconVisible="False" LeftMargin="229.4691" RightMargin="260.5309" TopMargin="628.1142" BottomMargin="283.8858" TouchEnable="True" FontSize="14" ButtonText="Button" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="120" Scale9Height="26" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="150.0000" Y="48.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="304.4691" Y="307.8858" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4757" Y="0.3207" />
            <PreSize X="0.2344" Y="0.0500" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
            <NormalFileData Type="PlistSubImage" Path="btn_finish.png" Plist="assets/ui/shoot_background.plist" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>