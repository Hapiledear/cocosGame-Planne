<GameFile>
  <PropertyGroup Name="GameScene" Type="Scene" ID="0e30d478-a3b9-4499-81eb-94729a83446c" Version="2.3.3.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" Tag="5" ctype="GameNodeObjectData">
        <Size X="640.0000" Y="960.0000" />
        <Children>
          <AbstractNodeData Name="background_1" ActionTag="-949263688" Tag="6" IconVisible="False" LeftMargin="0.0001" RightMargin="159.9999" TopMargin="108.0000" ctype="SpriteObjectData">
            <Size X="480.0000" Y="852.0000" />
            <AnchorPoint />
            <Position X="0.0001" />
            <Scale ScaleX="1.3300" ScaleY="1.1200" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.7500" Y="0.8875" />
            <FileData Type="PlistSubImage" Path="background.png" Plist="assets/ui/shoot_background.plist" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="hero1" ActionTag="1752212003" Tag="7" IconVisible="False" LeftMargin="283.0095" RightMargin="254.9905" TopMargin="699.1919" BottomMargin="134.8081" ctype="SpriteObjectData">
            <Size X="102.0000" Y="126.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="334.0095" Y="197.8081" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5219" Y="0.2061" />
            <PreSize X="0.1594" Y="0.1312" />
            <FileData Type="PlistSubImage" Path="hero1.png" Plist="assets/ui/shoot.plist" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="pause_btn" ActionTag="1696054395" CallBackType="Click" Tag="9" IconVisible="False" LeftMargin="573.5799" RightMargin="6.4201" TopMargin="4.6950" BottomMargin="910.3050" TouchEnable="True" FontSize="14" ButtonText="Button" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="30" Scale9Height="23" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="60.0000" Y="45.0000" />
            <AnchorPoint ScaleX="0.5484" ScaleY="0.4367" />
            <Position X="606.4825" Y="929.9548" />
            <Scale ScaleX="1.0789" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9476" Y="0.9687" />
            <PreSize X="0.0938" Y="0.0469" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="PlistSubImage" Path="game_pause_pressed.png" Plist="assets/ui/shoot.plist" />
            <NormalFileData Type="PlistSubImage" Path="game_pause_nor.png" Plist="assets/ui/shoot.plist" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="resume_btn" Visible="False" ActionTag="1233270967" CallBackType="Click" Tag="10" IconVisible="False" LeftMargin="576.0000" RightMargin="4.0000" TopMargin="8.5000" BottomMargin="906.5000" TouchEnable="True" FontSize="14" ButtonText="Button" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="30" Scale9Height="23" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="60.0000" Y="45.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="606.0000" Y="929.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9469" Y="0.9677" />
            <PreSize X="0.0938" Y="0.0469" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="PlistSubImage" Path="game_resume_pressed.png" Plist="assets/ui/shoot.plist" />
            <NormalFileData Type="PlistSubImage" Path="game_resume_nor.png" Plist="assets/ui/shoot.plist" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>