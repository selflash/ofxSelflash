﻿#pragma once

#include "ofMain.h"
#include "../ofxSelflash.h"
//#include "../display/Sprite.h"
//#include "../texts/TextField.h"
//#include "../ui/Button.h"
//#include "../ui/Slider.h"
//#include "../ui/NumberDialer.h"
//#include "../ui/ColorSlider.h"
//#include "../ui/Joystick.h"
//#include "../ui/ComboBox.h"
//#include "../ui/Pad2D.h"
//#include "../ui/RadioButton.h"
//#include "../ui/CircleColorPicker.h"

//using namespace fl2d;

class BasicController : public flSprite {
    public:
        flTextField* titleTf;
        flButton* minimizeButton;
        flButton* xButton;
        
        //--------------------------------------
        //テキストフィールド(000)
        flTextField* text000; flTextField* text001; flTextField* text002;
        flTextField* text003; flTextField* text004; flTextField* text005;
        flTextField* text006; flTextField* text007; flTextField* text008;
        flTextField* text009;
        flTextField* text010; flTextField* text011; flTextField* text012;
        flTextField* text013; flTextField* text014; flTextField* text015;
        flTextField* text016; flTextField* text017; flTextField* text018;
        flTextField* text019;
        flTextField* text020; flTextField* text021; flTextField* text022;
        flTextField* text023; flTextField* text024; flTextField* text025;
        flTextField* text026; flTextField* text027; flTextField* text028;
        flTextField* text029;
        flTextField* text030; flTextField* text031; flTextField* text032;
        flTextField* text033; flTextField* text034; flTextField* text035;
        flTextField* text036; flTextField* text037; flTextField* text038;
        flTextField* text039;
        //テキストフィールド(100)    
        flTextField* text100; flTextField* text101; flTextField* text102;
        flTextField* text103; flTextField* text104; flTextField* text105;
        flTextField* text106; flTextField* text107; flTextField* text108;
        flTextField* text109;
        flTextField* text110; flTextField* text111; flTextField* text112;
        flTextField* text113; flTextField* text114; flTextField* text115;
        flTextField* text116; flTextField* text117; flTextField* text118;
        flTextField* text119;
        flTextField* text120; flTextField* text121; flTextField* text122;
        flTextField* text123; flTextField* text124; flTextField* text125;
        flTextField* text126; flTextField* text127; flTextField* text128;
        flTextField* text129;
        flTextField* text130; flTextField* text131; flTextField* text132;
        flTextField* text133; flTextField* text134; flTextField* text135;
        flTextField* text136; flTextField* text137; flTextField* text138;
        flTextField* text139;
        //テキストフィールド(200)    
        flTextField* text200; flTextField* text201; flTextField* text202;
        flTextField* text203; flTextField* text204; flTextField* text205;
        flTextField* text206; flTextField* text207; flTextField* text208;
        flTextField* text209;
        flTextField* text210; flTextField* text211; flTextField* text212;
        flTextField* text213; flTextField* text214; flTextField* text215;
        flTextField* text216; flTextField* text217; flTextField* text218;
        flTextField* text219;
        flTextField* text220; flTextField* text221; flTextField* text222;
        flTextField* text223; flTextField* text224; flTextField* text225;
        flTextField* text226; flTextField* text227; flTextField* text228;
        flTextField* text229;
        flTextField* text230; flTextField* text231; flTextField* text232;
        flTextField* text233; flTextField* text234; flTextField* text235;
        flTextField* text236; flTextField* text237; flTextField* text238;
        flTextField* text239;
        //テキストフィールド(300)    
        flTextField* text300; flTextField* text301; flTextField* text302;
        flTextField* text303; flTextField* text304; flTextField* text305;
        flTextField* text306; flTextField* text307; flTextField* text308;
        flTextField* text309;
        flTextField* text310; flTextField* text311; flTextField* text312;
        flTextField* text313; flTextField* text314; flTextField* text315;
        flTextField* text316; flTextField* text317; flTextField* text318;
        flTextField* text319;
        flTextField* text320; flTextField* text321; flTextField* text322;
        flTextField* text323; flTextField* text324; flTextField* text325;
        flTextField* text326; flTextField* text327; flTextField* text328;
        flTextField* text329;
        flTextField* text330; flTextField* text331; flTextField* text332;
        flTextField* text333; flTextField* text334; flTextField* text335;
        flTextField* text336; flTextField* text337; flTextField* text338;
        flTextField* text339;
        //テキストフィールド(400)    
        flTextField* text400; flTextField* text401; flTextField* text402;
        flTextField* text403; flTextField* text404; flTextField* text405;
        flTextField* text406; flTextField* text407; flTextField* text408;
        flTextField* text409;
        flTextField* text410; flTextField* text411; flTextField* text412;
        flTextField* text413; flTextField* text414; flTextField* text415;
        flTextField* text416; flTextField* text417; flTextField* text418;
        flTextField* text419;
        flTextField* text420; flTextField* text421; flTextField* text422;
        flTextField* text423; flTextField* text424; flTextField* text425;
        flTextField* text426; flTextField* text427; flTextField* text428;
        flTextField* text429;
        flTextField* text430; flTextField* text431; flTextField* text432;
        flTextField* text433; flTextField* text434; flTextField* text435;
        flTextField* text436; flTextField* text437; flTextField* text438;
        flTextField* text439;
        //テキストフィールド(500)    
        flTextField* text500; flTextField* text501; flTextField* text502;
        flTextField* text503; flTextField* text504; flTextField* text505;
        flTextField* text506; flTextField* text507; flTextField* text508;
        flTextField* text509;
        flTextField* text510; flTextField* text511; flTextField* text512;
        flTextField* text513; flTextField* text514; flTextField* text515;
        flTextField* text516; flTextField* text517; flTextField* text518;
        flTextField* text519;
        flTextField* text520; flTextField* text521; flTextField* text522;
        flTextField* text523; flTextField* text524; flTextField* text525;
        flTextField* text526; flTextField* text527; flTextField* text528;
        flTextField* text529;
        flTextField* text530; flTextField* text531; flTextField* text532;
        flTextField* text533; flTextField* text534; flTextField* text535;
        flTextField* text536; flTextField* text537; flTextField* text538;
        flTextField* text539;
        //テキストフィールド(600)
        flTextField* text600; flTextField* text601; flTextField* text602;
        flTextField* text603; flTextField* text604; flTextField* text605;
        flTextField* text606; flTextField* text607; flTextField* text608;
        flTextField* text609;
        flTextField* text610; flTextField* text611; flTextField* text612;
        flTextField* text613; flTextField* text614; flTextField* text615;
        flTextField* text616; flTextField* text617; flTextField* text618;
        flTextField* text619;
        flTextField* text620; flTextField* text621; flTextField* text622;
        flTextField* text623; flTextField* text624; flTextField* text625;
        flTextField* text626; flTextField* text627; flTextField* text628;
        flTextField* text629;
        flTextField* text630; flTextField* text631; flTextField* text632;
        flTextField* text633; flTextField* text634; flTextField* text635;
        flTextField* text636; flTextField* text637; flTextField* text638;
        flTextField* text639;
        //--------------------------------------
        
        //--------------------------------------
        //ボタン(000)
        flButton* btn000; flButton* btn001; flButton* btn002; flButton* btn003; flButton* btn004;
        flButton* btn005; flButton* btn006; flButton* btn007; flButton* btn008; flButton* btn009;
        flButton* btn010; flButton* btn011; flButton* btn012; flButton* btn013; flButton* btn014;
        flButton* btn015; flButton* btn016; flButton* btn017; flButton* btn018; flButton* btn019;
        flButton* btn020; flButton* btn021; flButton* btn022; flButton* btn023; flButton* btn024;
        flButton* btn025; flButton* btn026; flButton* btn027; flButton* btn028; flButton* btn029;
        flButton* btn030; flButton* btn031; flButton* btn032; flButton* btn033; flButton* btn034;
        flButton* btn035; flButton* btn036; flButton* btn037; flButton* btn038; flButton* btn039;
        flButton* btn040; flButton* btn041; flButton* btn042; flButton* btn043; flButton* btn044;
        flButton* btn045; flButton* btn046; flButton* btn047; flButton* btn048; flButton* btn049;
        flButton* btn050; flButton* btn051; flButton* btn052; flButton* btn053; flButton* btn054;
        flButton* btn055; flButton* btn056; flButton* btn057; flButton* btn058; flButton* btn059;
        //ボタン(100)
        flButton* btn100; flButton* btn101; flButton* btn102; flButton* btn103; flButton* btn104;
        flButton* btn105; flButton* btn106; flButton* btn107; flButton* btn108; flButton* btn109;
        flButton* btn110; flButton* btn111; flButton* btn112; flButton* btn113; flButton* btn114;
        flButton* btn115; flButton* btn116; flButton* btn117; flButton* btn118; flButton* btn119;
        flButton* btn120; flButton* btn121; flButton* btn122; flButton* btn123; flButton* btn124;
        flButton* btn125; flButton* btn126; flButton* btn127; flButton* btn128; flButton* btn129;
        //ボタン(200)
        flButton* btn200; flButton* btn201; flButton* btn202; flButton* btn203; flButton* btn204;
        flButton* btn205; flButton* btn206; flButton* btn207; flButton* btn208; flButton* btn209;
        flButton* btn210; flButton* btn211; flButton* btn212; flButton* btn213; flButton* btn214;
        flButton* btn215; flButton* btn216; flButton* btn217; flButton* btn218; flButton* btn219;
        flButton* btn220; flButton* btn221; flButton* btn222; flButton* btn223; flButton* btn224;
        flButton* btn225; flButton* btn226; flButton* btn227; flButton* btn228; flButton* btn229;
        //ボタン(300)
        flButton* btn300; flButton* btn301; flButton* btn302; flButton* btn303; flButton* btn304;
        flButton* btn305; flButton* btn306; flButton* btn307; flButton* btn308; flButton* btn309;
        flButton* btn310;
        //ボタン(400)
        flButton* btn400; flButton* btn401; flButton* btn402; flButton* btn403; flButton* btn404;
        flButton* btn405; flButton* btn406; flButton* btn407; flButton* btn408; flButton* btn409;
        flButton* btn410;
        //ボタン(500)
        flButton* btn500; flButton* btn501; flButton* btn502; flButton* btn503; flButton* btn504;
        flButton* btn505; flButton* btn506; flButton* btn507; flButton* btn508; flButton* btn509;
        flButton* btn510;
        //ボタン(600)
        flButton* btn600; flButton* btn601; flButton* btn602; flButton* btn603; flButton* btn604;
        flButton* btn605; flButton* btn606; flButton* btn607; flButton* btn608; flButton* btn609;
        flButton* btn610;
        //ボタン(700)
        flButton* btn700; flButton* btn701; flButton* btn702; flButton* btn703; flButton* btn704;
        flButton* btn705; flButton* btn706; flButton* btn707; flButton* btn708; flButton* btn709;
        flButton* btn710;
        //ボタン(800)
        flButton* btn800; flButton* btn801; flButton* btn802; flButton* btn803; flButton* btn804;
        flButton* btn805; flButton* btn806; flButton* btn807; flButton* btn808; flButton* btn809;
        flButton* btn810;
        //ボタン(900)
        flButton* btn900; flButton* btn901; flButton* btn902; flButton* btn903; flButton* btn904;
        flButton* btn905; flButton* btn906; flButton* btn907; flButton* btn908; flButton* btn909;
        flButton* btn910;
        //--------------------------------------
        
        //--------------------------------------
        //スライダー(000)
        flSlider* slider000; flSlider* slider001; flSlider* slider002; flSlider* slider003;
        flSlider* slider004; flSlider* slider005; flSlider* slider006; flSlider* slider007;
        flSlider* slider008; flSlider* slider009;
        flSlider* slider010; flSlider* slider011; flSlider* slider012; flSlider* slider013;
        flSlider* slider014; flSlider* slider015; flSlider* slider016; flSlider* slider017;
        flSlider* slider018; flSlider* slider019;
        flSlider* slider020; flSlider* slider021; flSlider* slider022; flSlider* slider023;
        flSlider* slider024; flSlider* slider025; flSlider* slider026; flSlider* slider027;
        flSlider* slider028; flSlider* slider029;
        //スライダー(100)
        flSlider* slider100; flSlider* slider101; flSlider* slider102; flSlider* slider103;
        flSlider* slider104; flSlider* slider105; flSlider* slider106; flSlider* slider107;
        flSlider* slider108; flSlider* slider109;
        flSlider* slider110; flSlider* slider111; flSlider* slider112; flSlider* slider113;
        flSlider* slider114; flSlider* slider115; flSlider* slider116; flSlider* slider117;
        flSlider* slider118; flSlider* slider119;
        flSlider* slider120; flSlider* slider121; flSlider* slider122; flSlider* slider123;
        flSlider* slider124; flSlider* slider125; flSlider* slider126; flSlider* slider127;
        flSlider* slider128; flSlider* slider129;
        //スライダー(200)
        flSlider* slider200; flSlider* slider201; flSlider* slider202; flSlider* slider203;
        flSlider* slider204; flSlider* slider205; flSlider* slider206; flSlider* slider207;
        flSlider* slider208; flSlider* slider209;
        flSlider* slider210; flSlider* slider211; flSlider* slider212; flSlider* slider213;
        flSlider* slider214; flSlider* slider215; flSlider* slider216; flSlider* slider217;
        flSlider* slider218; flSlider* slider219;
        flSlider* slider220; flSlider* slider221; flSlider* slider222; flSlider* slider223;
        flSlider* slider224; flSlider* slider225; flSlider* slider226; flSlider* slider227;
        flSlider* slider228; flSlider* slider229;
        //スライダー(300)
        flSlider* slider300; flSlider* slider301; flSlider* slider302; flSlider* slider303;
        flSlider* slider304; flSlider* slider305; flSlider* slider306; flSlider* slider307;
        flSlider* slider308; flSlider* slider309;
        flSlider* slider310; flSlider* slider311; flSlider* slider312; flSlider* slider313;
        flSlider* slider314; flSlider* slider315; flSlider* slider316; flSlider* slider317;
        flSlider* slider318; flSlider* slider319;
        flSlider* slider320; flSlider* slider321; flSlider* slider322; flSlider* slider323;
        flSlider* slider324; flSlider* slider325; flSlider* slider326; flSlider* slider327;
        flSlider* slider328; flSlider* slider329;
        //スライダー(400)
        flSlider* slider400; flSlider* slider401; flSlider* slider402; flSlider* slider403;
        flSlider* slider404; flSlider* slider405; flSlider* slider406; flSlider* slider407;
        flSlider* slider408; flSlider* slider409;
        flSlider* slider410; flSlider* slider411; flSlider* slider412; flSlider* slider413;
        flSlider* slider414; flSlider* slider415; flSlider* slider416; flSlider* slider417;
        flSlider* slider418; flSlider* slider419;
        flSlider* slider420; flSlider* slider421; flSlider* slider422; flSlider* slider423;
        flSlider* slider424; flSlider* slider425; flSlider* slider426; flSlider* slider427;
        flSlider* slider428; flSlider* slider429;
        //スライダー(500)
        flSlider* slider500; flSlider* slider501; flSlider* slider502; flSlider* slider503;
        flSlider* slider504; flSlider* slider505; flSlider* slider506; flSlider* slider507;
        flSlider* slider508; flSlider* slider509;
        flSlider* slider510; flSlider* slider511; flSlider* slider512; flSlider* slider513;
        flSlider* slider514; flSlider* slider515; flSlider* slider516; flSlider* slider517;
        flSlider* slider518; flSlider* slider519;
        flSlider* slider520; flSlider* slider521; flSlider* slider522; flSlider* slider523;
        flSlider* slider524; flSlider* slider525; flSlider* slider526; flSlider* slider527;
        flSlider* slider528; flSlider* slider529;
        //スライダー(600)
        flSlider* slider600; flSlider* slider601; flSlider* slider602; flSlider* slider603;
        flSlider* slider604; flSlider* slider605; flSlider* slider606; flSlider* slider607;
        flSlider* slider608; flSlider* slider609;
        flSlider* slider610; flSlider* slider611; flSlider* slider612; flSlider* slider613;
        flSlider* slider614; flSlider* slider615; flSlider* slider616; flSlider* slider617;
        flSlider* slider618; flSlider* slider619;
        flSlider* slider620; flSlider* slider621; flSlider* slider622; flSlider* slider623;
        flSlider* slider624; flSlider* slider625; flSlider* slider626; flSlider* slider627;
        flSlider* slider628; flSlider* slider629;
        //--------------------------------------

        //--------------------------------------
        //レンジスライダー(000)
        flRangeSlider* rangeSlider000; flRangeSlider* rangeSlider001; flRangeSlider* rangeSlider002; flRangeSlider* rangeSlider003;
        flRangeSlider* rangeSlider004; flRangeSlider* rangeSlider005; flRangeSlider* rangeSlider006; flRangeSlider* rangeSlider007;
        flRangeSlider* rangeSlider008; flRangeSlider* rangeSlider009;
        flRangeSlider* rangeSlider010; flRangeSlider* rangeSlider011; flRangeSlider* rangeSlider012; flRangeSlider* rangeSlider013;
        flRangeSlider* rangeSlider014; flRangeSlider* rangeSlider015; flRangeSlider* rangeSlider016; flRangeSlider* rangeSlider017;
        flRangeSlider* rangeSlider018; flRangeSlider* rangeSlider019;
        flRangeSlider* rangeSlider020; flRangeSlider* rangeSlider021; flRangeSlider* rangeSlider022; flRangeSlider* rangeSlider023;
        flRangeSlider* rangeSlider024; flRangeSlider* rangeSlider025; flRangeSlider* rangeSlider026; flRangeSlider* rangeSlider027;
        flRangeSlider* rangeSlider028; flRangeSlider* rangeSlider029;
        //レンジスライダー(100)
        flRangeSlider* rangeSlider100; flRangeSlider* rangeSlider101; flRangeSlider* rangeSlider102; flRangeSlider* rangeSlider103;
        flRangeSlider* rangeSlider104; flRangeSlider* rangeSlider105; flRangeSlider* rangeSlider106; flRangeSlider* rangeSlider107;
        flRangeSlider* rangeSlider108; flRangeSlider* rangeSlider109;
        flRangeSlider* rangeSlider110; flRangeSlider* rangeSlider111; flRangeSlider* rangeSlider112; flRangeSlider* rangeSlider113;
        flRangeSlider* rangeSlider114; flRangeSlider* rangeSlider115; flRangeSlider* rangeSlider116; flRangeSlider* rangeSlider117;
        flRangeSlider* rangeSlider118; flRangeSlider* rangeSlider119;
        flRangeSlider* rangeSlider120; flRangeSlider* rangeSlider121; flRangeSlider* rangeSlider122; flRangeSlider* rangeSlider123;
        flRangeSlider* rangeSlider124; flRangeSlider* rangeSlider125; flRangeSlider* rangeSlider126; flRangeSlider* rangeSlider127;
        flRangeSlider* rangeSlider128; flRangeSlider* rangeSlider129;
        //レンジスライダー(200)
        flRangeSlider* rangeSlider200; flRangeSlider* rangeSlider201; flRangeSlider* rangeSlider202; flRangeSlider* rangeSlider203;
        flRangeSlider* rangeSlider204; flRangeSlider* rangeSlider205; flRangeSlider* rangeSlider206; flRangeSlider* rangeSlider207;
        flRangeSlider* rangeSlider208; flRangeSlider* rangeSlider209;
        flRangeSlider* rangeSlider210; flRangeSlider* rangeSlider211; flRangeSlider* rangeSlider212; flRangeSlider* rangeSlider213;
        flRangeSlider* rangeSlider214; flRangeSlider* rangeSlider215; flRangeSlider* rangeSlider216; flRangeSlider* rangeSlider217;
        flRangeSlider* rangeSlider218; flRangeSlider* rangeSlider219;
        flRangeSlider* rangeSlider220; flRangeSlider* rangeSlider221; flRangeSlider* rangeSlider222; flRangeSlider* rangeSlider223;
        flRangeSlider* rangeSlider224; flRangeSlider* rangeSlider225; flRangeSlider* rangeSlider226; flRangeSlider* rangeSlider227;
        flRangeSlider* rangeSlider228; flRangeSlider* rangeSlider229;
        //レンジスライダー(300)
        flRangeSlider* rangeSlider300; flRangeSlider* rangeSlider301; flRangeSlider* rangeSlider302; flRangeSlider* rangeSlider303;
        flRangeSlider* rangeSlider304; flRangeSlider* rangeSlider305; flRangeSlider* rangeSlider306; flRangeSlider* rangeSlider307;
        flRangeSlider* rangeSlider308; flRangeSlider* rangeSlider309;
        flRangeSlider* rangeSlider310; flRangeSlider* rangeSlider311; flRangeSlider* rangeSlider312; flRangeSlider* rangeSlider313;
        flRangeSlider* rangeSlider314; flRangeSlider* rangeSlider315; flRangeSlider* rangeSlider316; flRangeSlider* rangeSlider317;
        flRangeSlider* rangeSlider318; flRangeSlider* rangeSlider319;
        flRangeSlider* rangeSlider320; flRangeSlider* rangeSlider321; flRangeSlider* rangeSlider322; flRangeSlider* rangeSlider323;
        flRangeSlider* rangeSlider324; flRangeSlider* rangeSlider325; flRangeSlider* rangeSlider326; flRangeSlider* rangeSlider327;
        flRangeSlider* rangeSlider328; flRangeSlider* rangeSlider329;
        //レンジスライダー(400)
        flRangeSlider* rangeSlider400; flRangeSlider* rangeSlider401; flRangeSlider* rangeSlider402; flRangeSlider* rangeSlider403;
        flRangeSlider* rangeSlider404; flRangeSlider* rangeSlider405; flRangeSlider* rangeSlider406; flRangeSlider* rangeSlider407;
        flRangeSlider* rangeSlider408; flRangeSlider* rangeSlider409;
        flRangeSlider* rangeSlider410; flRangeSlider* rangeSlider411; flRangeSlider* rangeSlider412; flRangeSlider* rangeSlider413;
        flRangeSlider* rangeSlider414; flRangeSlider* rangeSlider415; flRangeSlider* rangeSlider416; flRangeSlider* rangeSlider417;
        flRangeSlider* rangeSlider418; flRangeSlider* rangeSlider419;
        flRangeSlider* rangeSlider420; flRangeSlider* rangeSlider421; flRangeSlider* rangeSlider422; flRangeSlider* rangeSlider423;
        flRangeSlider* rangeSlider424; flRangeSlider* rangeSlider425; flRangeSlider* rangeSlider426; flRangeSlider* rangeSlider427;
        flRangeSlider* rangeSlider428; flRangeSlider* rangeSlider429;
        //レンジスライダー(500)
        flRangeSlider* rangeSlider500; flRangeSlider* rangeSlider501; flRangeSlider* rangeSlider502; flRangeSlider* rangeSlider503;
        flRangeSlider* rangeSlider504; flRangeSlider* rangeSlider505; flRangeSlider* rangeSlider506; flRangeSlider* rangeSlider507;
        flRangeSlider* rangeSlider508; flRangeSlider* rangeSlider509;
        flRangeSlider* rangeSlider510; flRangeSlider* rangeSlider511; flRangeSlider* rangeSlider512; flRangeSlider* rangeSlider513;
        flRangeSlider* rangeSlider514; flRangeSlider* rangeSlider515; flRangeSlider* rangeSlider516; flRangeSlider* rangeSlider517;
        flRangeSlider* rangeSlider518; flRangeSlider* rangeSlider519;
        flRangeSlider* rangeSlider520; flRangeSlider* rangeSlider521; flRangeSlider* rangeSlider522; flRangeSlider* rangeSlider523;
        flRangeSlider* rangeSlider524; flRangeSlider* rangeSlider525; flRangeSlider* rangeSlider526; flRangeSlider* rangeSlider527;
        flRangeSlider* rangeSlider528; flRangeSlider* rangeSlider529;
        //レンジスライダー(600)
        flRangeSlider* rangeSlider600; flRangeSlider* rangeSlider601; flRangeSlider* rangeSlider602; flRangeSlider* rangeSlider603;
        flRangeSlider* rangeSlider604; flRangeSlider* rangeSlider605; flRangeSlider* rangeSlider606; flRangeSlider* rangeSlider607;
        flRangeSlider* rangeSlider608; flRangeSlider* rangeSlider609;
        flRangeSlider* rangeSlider610; flRangeSlider* rangeSlider611; flRangeSlider* rangeSlider612; flRangeSlider* rangeSlider613;
        flRangeSlider* rangeSlider614; flRangeSlider* rangeSlider615; flRangeSlider* rangeSlider616; flRangeSlider* rangeSlider617;
        flRangeSlider* rangeSlider618; flRangeSlider* rangeSlider619;
        flRangeSlider* rangeSlider620; flRangeSlider* rangeSlider621; flRangeSlider* rangeSlider622; flRangeSlider* rangeSlider623;
        flRangeSlider* rangeSlider624; flRangeSlider* rangeSlider625; flRangeSlider* rangeSlider626; flRangeSlider* rangeSlider627;
        flRangeSlider* rangeSlider628; flRangeSlider* rangeSlider629;
        //--------------------------------------
        
        //--------------------------------------
        //カラースライダー(000)
        flColorSlider* colorSlider000; flColorSlider* colorSlider001; flColorSlider* colorSlider002; flColorSlider* colorSlider003;
        flColorSlider* colorSlider004; flColorSlider* colorSlider005; flColorSlider* colorSlider006; flColorSlider* colorSlider007;
        flColorSlider* colorSlider008; flColorSlider* colorSlider009;
        flColorSlider* colorSlider010; flColorSlider* colorSlider011; flColorSlider* colorSlider012; flColorSlider* colorSlider013;
        flColorSlider* colorSlider014; flColorSlider* colorSlider015; flColorSlider* colorSlider016; flColorSlider* colorSlider017;
        flColorSlider* colorSlider018; flColorSlider* colorSlider019;
        flColorSlider* colorSlider020; flColorSlider* colorSlider021; flColorSlider* colorSlider022; flColorSlider* colorSlider023;
        flColorSlider* colorSlider024; flColorSlider* colorSlider025; flColorSlider* colorSlider026; flColorSlider* colorSlider027;
        flColorSlider* colorSlider028; flColorSlider* colorSlider029;
        //RGBライダー(100)
        flColorSlider* colorSlider100; flColorSlider* colorSlider101; flColorSlider* colorSlider102; flColorSlider* colorSlider103;
        flColorSlider* colorSlider104; flColorSlider* colorSlider105; flColorSlider* colorSlider106; flColorSlider* colorSlider107;
        flColorSlider* colorSlider108; flColorSlider* colorSlider109;
        flColorSlider* colorSlider110; flColorSlider* colorSlider111; flColorSlider* colorSlider112; flColorSlider* colorSlider113;
        flColorSlider* colorSlider114; flColorSlider* colorSlider115; flColorSlider* colorSlider116; flColorSlider* colorSlider117;
        flColorSlider* colorSlider118; flColorSlider* colorSlider119;
        flColorSlider* colorSlider120; flColorSlider* colorSlider121; flColorSlider* colorSlider122; flColorSlider* colorSlider123;
        flColorSlider* colorSlider124; flColorSlider* colorSlider125; flColorSlider* colorSlider126; flColorSlider* colorSlider127;
        flColorSlider* colorSlider128; flColorSlider* colorSlider129;
        //カラースライダー(200)
        flColorSlider* colorSlider200; flColorSlider* colorSlider201; flColorSlider* colorSlider202; flColorSlider* colorSlider203;
        flColorSlider* colorSlider204; flColorSlider* colorSlider205; flColorSlider* colorSlider206; flColorSlider* colorSlider207;
        flColorSlider* colorSlider208; flColorSlider* colorSlider209;
        flColorSlider* colorSlider210; flColorSlider* colorSlider211; flColorSlider* colorSlider212; flColorSlider* colorSlider213;
        flColorSlider* colorSlider214; flColorSlider* colorSlider215; flColorSlider* colorSlider216; flColorSlider* colorSlider217;
        flColorSlider* colorSlider218; flColorSlider* colorSlider219;
        flColorSlider* colorSlider220; flColorSlider* colorSlider221; flColorSlider* colorSlider222; flColorSlider* colorSlider223;
        flColorSlider* colorSlider224; flColorSlider* colorSlider225; flColorSlider* colorSlider226; flColorSlider* colorSlider227;
        flColorSlider* colorSlider228; flColorSlider* colorSlider229;
        //カラースライダー(300)
        flColorSlider* colorSlider300; flColorSlider* colorSlider301; flColorSlider* colorSlider302; flColorSlider* colorSlider303;
        flColorSlider* colorSlider304; flColorSlider* colorSlider305; flColorSlider* colorSlider306; flColorSlider* colorSlider307;
        flColorSlider* colorSlider308; flColorSlider* colorSlider309;
        flColorSlider* colorSlider310; flColorSlider* colorSlider311; flColorSlider* colorSlider312; flColorSlider* colorSlider313;
        flColorSlider* colorSlider314; flColorSlider* colorSlider315; flColorSlider* colorSlider316; flColorSlider* colorSlider317;
        flColorSlider* colorSlider318; flColorSlider* colorSlider319;
        flColorSlider* colorSlider320; flColorSlider* colorSlider321; flColorSlider* colorSlider322; flColorSlider* colorSlider323;
        flColorSlider* colorSlider324; flColorSlider* colorSlider325; flColorSlider* colorSlider326; flColorSlider* colorSlider327;
        flColorSlider* colorSlider328; flColorSlider* colorSlider329;
        //カラースライダー(400)
        flColorSlider* colorSlider400; flColorSlider* colorSlider401; flColorSlider* colorSlider402; flColorSlider* colorSlider403;
        flColorSlider* colorSlider404; flColorSlider* colorSlider405; flColorSlider* colorSlider406; flColorSlider* colorSlider407;
        flColorSlider* colorSlider408; flColorSlider* colorSlider409;
        flColorSlider* colorSlider410; flColorSlider* colorSlider411; flColorSlider* colorSlider412; flColorSlider* colorSlider413;
        flColorSlider* colorSlider414; flColorSlider* colorSlider415; flColorSlider* colorSlider416; flColorSlider* colorSlider417;
        flColorSlider* colorSlider418; flColorSlider* colorSlider419;
        flColorSlider* colorSlider420; flColorSlider* colorSlider421; flColorSlider* colorSlider422; flColorSlider* colorSlider423;
        flColorSlider* colorSlider424; flColorSlider* colorSlider425; flColorSlider* colorSlider426; flColorSlider* colorSlider427;
        flColorSlider* colorSlider428; flColorSlider* colorSlider429;
        //カラースライダー(500)
        flColorSlider* colorSlider500; flColorSlider* colorSlider501; flColorSlider* colorSlider502; flColorSlider* colorSlider503;
        flColorSlider* colorSlider504; flColorSlider* colorSlider505; flColorSlider* colorSlider506; flColorSlider* colorSlider507;
        flColorSlider* colorSlider508; flColorSlider* colorSlider509;
        flColorSlider* colorSlider510; flColorSlider* colorSlider511; flColorSlider* colorSlider512; flColorSlider* colorSlider513;
        flColorSlider* colorSlider514; flColorSlider* colorSlider515; flColorSlider* colorSlider516; flColorSlider* colorSlider517;
        flColorSlider* colorSlider518; flColorSlider* colorSlider519;
        flColorSlider* colorSlider520; flColorSlider* colorSlider521; flColorSlider* colorSlider522; flColorSlider* colorSlider523;
        flColorSlider* colorSlider524; flColorSlider* colorSlider525; flColorSlider* colorSlider526; flColorSlider* colorSlider527;
        flColorSlider* colorSlider528; flColorSlider* colorSlider529;
        //カラースライダー(600)
        flColorSlider* colorSlider600; flColorSlider* colorSlider601; flColorSlider* colorSlider602; flColorSlider* colorSlider603;
        flColorSlider* colorSlider604; flColorSlider* colorSlider605; flColorSlider* colorSlider606; flColorSlider* colorSlider607;
        flColorSlider* colorSlider608; flColorSlider* colorSlider609;
        flColorSlider* colorSlider610; flColorSlider* colorSlider611; flColorSlider* colorSlider612; flColorSlider* colorSlider613;
        flColorSlider* colorSlider614; flColorSlider* colorSlider615; flColorSlider* colorSlider616; flColorSlider* colorSlider617;
        flColorSlider* colorSlider618; flColorSlider* colorSlider619;
        flColorSlider* colorSlider620; flColorSlider* colorSlider621; flColorSlider* colorSlider622; flColorSlider* colorSlider623;
        flColorSlider* colorSlider624; flColorSlider* colorSlider625; flColorSlider* colorSlider626; flColorSlider* colorSlider627;
        flColorSlider* colorSlider628; flColorSlider* colorSlider629;
        //カラースライダー(700)
        flColorSlider* colorSlider700; flColorSlider* colorSlider701; flColorSlider* colorSlider702; flColorSlider* colorSlider703;
        flColorSlider* colorSlider704; flColorSlider* colorSlider705; flColorSlider* colorSlider706; flColorSlider* colorSlider707;
        flColorSlider* colorSlider708; flColorSlider* colorSlider709;
        flColorSlider* colorSlider710; flColorSlider* colorSlider711; flColorSlider* colorSlider712; flColorSlider* colorSlider713;
        flColorSlider* colorSlider714; flColorSlider* colorSlider715; flColorSlider* colorSlider716; flColorSlider* colorSlider717;
        flColorSlider* colorSlider718; flColorSlider* colorSlider719;
        flColorSlider* colorSlider720; flColorSlider* colorSlider721; flColorSlider* colorSlider722; flColorSlider* colorSlider723;
        flColorSlider* colorSlider724; flColorSlider* colorSlider725; flColorSlider* colorSlider726; flColorSlider* colorSlider727;
        flColorSlider* colorSlider728; flColorSlider* colorSlider729;
        //カラースライダー(800)
        flColorSlider* colorSlider800; flColorSlider* colorSlider801; flColorSlider* colorSlider802; flColorSlider* colorSlider803;
        flColorSlider* colorSlider804; flColorSlider* colorSlider805; flColorSlider* colorSlider806; flColorSlider* colorSlider807;
        flColorSlider* colorSlider808; flColorSlider* colorSlider809;
        flColorSlider* colorSlider810; flColorSlider* colorSlider811; flColorSlider* colorSlider812; flColorSlider* colorSlider813;
        flColorSlider* colorSlider814; flColorSlider* colorSlider815; flColorSlider* colorSlider816; flColorSlider* colorSlider817;
        flColorSlider* colorSlider818; flColorSlider* colorSlider819;
        flColorSlider* colorSlider820; flColorSlider* colorSlider821; flColorSlider* colorSlider822; flColorSlider* colorSlider823;
        flColorSlider* colorSlider824; flColorSlider* colorSlider825; flColorSlider* colorSlider826; flColorSlider* colorSlider827;
        flColorSlider* colorSlider828; flColorSlider* colorSlider829;
        //--------------------------------------
        
        //--------------------------------------
        //ボタン(000)
        flNumberDialer* dialer000; flNumberDialer* dialer001; flNumberDialer* dialer002; flNumberDialer* dialer003; flNumberDialer* dialer004;
        flNumberDialer* dialer005; flNumberDialer* dialer006; flNumberDialer* dialer007; flNumberDialer* dialer008; flNumberDialer* dialer009;
        flNumberDialer* dialer010; flNumberDialer* dialer011; flNumberDialer* dialer012; flNumberDialer* dialer013; flNumberDialer* dialer014;
        flNumberDialer* dialer015; flNumberDialer* dialer016; flNumberDialer* dialer017; flNumberDialer* dialer018; flNumberDialer* dialer019;
        flNumberDialer* dialer020; flNumberDialer* dialer021; flNumberDialer* dialer022; flNumberDialer* dialer023; flNumberDialer* dialer024;
        flNumberDialer* dialer025; flNumberDialer* dialer026; flNumberDialer* dialer027; flNumberDialer* dialer028; flNumberDialer* dialer029;
        //ボタン(100)
        flNumberDialer* dialer100; flNumberDialer* dialer101; flNumberDialer* dialer102; flNumberDialer* dialer103; flNumberDialer* dialer104;
        flNumberDialer* dialer105; flNumberDialer* dialer106; flNumberDialer* dialer107; flNumberDialer* dialer108; flNumberDialer* dialer109;
        flNumberDialer* dialer110; flNumberDialer* dialer111; flNumberDialer* dialer112; flNumberDialer* dialer113; flNumberDialer* dialer114;
        flNumberDialer* dialer115; flNumberDialer* dialer116; flNumberDialer* dialer117; flNumberDialer* dialer118; flNumberDialer* dialer119;
        flNumberDialer* dialer120; flNumberDialer* dialer121; flNumberDialer* dialer122; flNumberDialer* dialer123; flNumberDialer* dialer124;
        flNumberDialer* dialer125; flNumberDialer* dialer126; flNumberDialer* dialer127; flNumberDialer* dialer128; flNumberDialer* dialer129;
        //ボタン(200)
        flNumberDialer* dialer200; flNumberDialer* dialer201; flNumberDialer* dialer202; flNumberDialer* dialer203; flNumberDialer* dialer204;
        flNumberDialer* dialer205; flNumberDialer* dialer206; flNumberDialer* dialer207; flNumberDialer* dialer208; flNumberDialer* dialer209;
        flNumberDialer* dialer210; flNumberDialer* dialer211; flNumberDialer* dialer212; flNumberDialer* dialer213; flNumberDialer* dialer214;
        flNumberDialer* dialer215; flNumberDialer* dialer216; flNumberDialer* dialer217; flNumberDialer* dialer218; flNumberDialer* dialer219;
        flNumberDialer* dialer220; flNumberDialer* dialer221; flNumberDialer* dialer222; flNumberDialer* dialer223; flNumberDialer* dialer224;
        flNumberDialer* dialer225; flNumberDialer* dialer226; flNumberDialer* dialer227; flNumberDialer* dialer228; flNumberDialer* dialer229;
        //ボタン(300)
        flNumberDialer* dialer300; flNumberDialer* dialer301; flNumberDialer* dialer302; flNumberDialer* dialer303; flNumberDialer* dialer304;
        flNumberDialer* dialer305; flNumberDialer* dialer306; flNumberDialer* dialer307; flNumberDialer* dialer308; flNumberDialer* dialer309;
        flNumberDialer* dialer310;
        //ボタン(400)
        flNumberDialer* dialer400; flNumberDialer* dialer401; flNumberDialer* dialer402; flNumberDialer* dialer403; flNumberDialer* dialer404;
        flNumberDialer* dialer405; flNumberDialer* dialer406; flNumberDialer* dialer407; flNumberDialer* dialer408; flNumberDialer* dialer409;
        flNumberDialer* dialer410;
        //ボタン(500)
        flNumberDialer* dialer500; flNumberDialer* dialer501; flNumberDialer* dialer502; flNumberDialer* dialer503; flNumberDialer* dialer504;
        flNumberDialer* dialer505; flNumberDialer* dialer506; flNumberDialer* dialer507; flNumberDialer* dialer508; flNumberDialer* dialer509;
        flNumberDialer* dialer510;
        //ボタン(600)
        flNumberDialer* dialer600; flNumberDialer* dialer601; flNumberDialer* dialer602; flNumberDialer* dialer603; flNumberDialer* dialer604;
        flNumberDialer* dialer605; flNumberDialer* dialer606; flNumberDialer* dialer607; flNumberDialer* dialer608; flNumberDialer* dialer609;
        flNumberDialer* dialer610;
        //ボタン(700)
        flNumberDialer* dialer700; flNumberDialer* dialer701; flNumberDialer* dialer702; flNumberDialer* dialer703; flNumberDialer* dialer704;
        flNumberDialer* dialer705; flNumberDialer* dialer706; flNumberDialer* dialer707; flNumberDialer* dialer708; flNumberDialer* dialer709;
        flNumberDialer* dialer710;
        //ボタン(800)
        flNumberDialer* dialer800; flNumberDialer* dialer801; flNumberDialer* dialer802; flNumberDialer* dialer803; flNumberDialer* dialer804;
        flNumberDialer* dialer805; flNumberDialer* dialer806; flNumberDialer* dialer807; flNumberDialer* dialer808; flNumberDialer* dialer809;
        flNumberDialer* dialer810;
        //ボタン(900)
        flNumberDialer* dialer900; flNumberDialer* dialer901; flNumberDialer* dialer902; flNumberDialer* dialer903; flNumberDialer* dialer904;
        flNumberDialer* dialer905; flNumberDialer* dialer906; flNumberDialer* dialer907; flNumberDialer* dialer908; flNumberDialer* dialer909;
        flNumberDialer* dialer910;
        //--------------------------------------
        
        //--------------------------------------
        //2Dパッド(000)
        flPad2D* pad000; flPad2D* pad001; flPad2D* pad002; flPad2D* pad003;
        flPad2D* pad004; flPad2D* pad005; flPad2D* pad006; flPad2D* pad007;
        flPad2D* pad008; flPad2D* pad009; flPad2D* pad010; flPad2D* pad011;
        flPad2D* pad012; flPad2D* pad013; flPad2D* pad014; flPad2D* pad015;
        flPad2D* pad016; flPad2D* pad017; flPad2D* pad018; flPad2D* pad019;
        //2Dパッド(100)
        flPad2D* pad100; flPad2D* pad101; flPad2D* pad102; flPad2D* pad103;
        flPad2D* pad104; flPad2D* pad105; flPad2D* pad106; flPad2D* pad107;
        flPad2D* pad108; flPad2D* pad109; flPad2D* pad110; flPad2D* pad111;
        flPad2D* pad112; flPad2D* pad113; flPad2D* pad114; flPad2D* pad115;
        flPad2D* pad116; flPad2D* pad117; flPad2D* pad118; flPad2D* pad119;
        //2Dパッド(200)
        flPad2D* pad200; flPad2D* pad201; flPad2D* pad202; flPad2D* pad203;
        flPad2D* pad204; flPad2D* pad205; flPad2D* pad206; flPad2D* pad207;
        flPad2D* pad208; flPad2D* pad209; flPad2D* pad210; flPad2D* pad211;
        flPad2D* pad212; flPad2D* pad213; flPad2D* pad214; flPad2D* pad215;
        flPad2D* pad216; flPad2D* pad217; flPad2D* pad218; flPad2D* pad219;
        //2Dパッド(300)
        flPad2D* pad300; flPad2D* pad301; flPad2D* pad302; flPad2D* pad303;
        flPad2D* pad304; flPad2D* pad305; flPad2D* pad306; flPad2D* pad307;
        flPad2D* pad308; flPad2D* pad309; flPad2D* pad310; flPad2D* pad311;
        flPad2D* pad312; flPad2D* pad313; flPad2D* pad314; flPad2D* pad315;
        flPad2D* pad316; flPad2D* pad317; flPad2D* pad318; flPad2D* pad319;
        //2Dパッド(400)
        flPad2D* pad400; flPad2D* pad401; flPad2D* pad402; flPad2D* pad403;
        flPad2D* pad404; flPad2D* pad405; flPad2D* pad406; flPad2D* pad407;
        flPad2D* pad408; flPad2D* pad409; flPad2D* pad410; flPad2D* pad411;
        flPad2D* pad412; flPad2D* pad413; flPad2D* pad414; flPad2D* pad415;
        flPad2D* pad416; flPad2D* pad417; flPad2D* pad418; flPad2D* pad419;
        //2Dパッド(500)
        flPad2D* pad500; flPad2D* pad501; flPad2D* pad502; flPad2D* pad503;
        flPad2D* pad504; flPad2D* pad505; flPad2D* pad506; flPad2D* pad507;
        flPad2D* pad508; flPad2D* pad509; flPad2D* pad510; flPad2D* pad511;
        flPad2D* pad512; flPad2D* pad513; flPad2D* pad514; flPad2D* pad515;
        flPad2D* pad516; flPad2D* pad517; flPad2D* pad518; flPad2D* pad519;
        //--------------------------------------
    
        //--------------------------------------
        //カラーピッカー(000)
        flCircleColorPicker* colorPicker000; flCircleColorPicker* colorPicker001; flCircleColorPicker* colorPicker002;
        flCircleColorPicker* colorPicker003; flCircleColorPicker* colorPicker004; flCircleColorPicker* colorPicker005;
        flCircleColorPicker* colorPicker006; flCircleColorPicker* colorPicker007; flCircleColorPicker* colorPicker008;
        flCircleColorPicker* colorPicker009; flCircleColorPicker* colorPicker010; flCircleColorPicker* colorPicker011;
        flCircleColorPicker* colorPicker012; flCircleColorPicker* colorPicker013; flCircleColorPicker* colorPicker014;
        flCircleColorPicker* colorPicker015; flCircleColorPicker* colorPicker016; flCircleColorPicker* colorPicker017;
        flCircleColorPicker* colorPicker018; flCircleColorPicker* colorPicker019;
        //カラーピッカー(100)
        flCircleColorPicker* colorPicker100; flCircleColorPicker* colorPicker101; flCircleColorPicker* colorPicker102;
        flCircleColorPicker* colorPicker103; flCircleColorPicker* colorPicker104; flCircleColorPicker* colorPicker105;
        flCircleColorPicker* colorPicker106; flCircleColorPicker* colorPicker107; flCircleColorPicker* colorPicker108;
        flCircleColorPicker* colorPicker109; flCircleColorPicker* colorPicker110; flCircleColorPicker* colorPicker111;
        flCircleColorPicker* colorPicker112; flCircleColorPicker* colorPicker113; flCircleColorPicker* colorPicker114;
        flCircleColorPicker* colorPicker115; flCircleColorPicker* colorPicker116; flCircleColorPicker* colorPicker117;
        flCircleColorPicker* colorPicker118; flCircleColorPicker* colorPicker119;
        //カラーピッカー(200)
        flCircleColorPicker* colorPicker200; flCircleColorPicker* colorPicker201; flCircleColorPicker* colorPicker202;
        flCircleColorPicker* colorPicker203; flCircleColorPicker* colorPicker204; flCircleColorPicker* colorPicker205;
        flCircleColorPicker* colorPicker206; flCircleColorPicker* colorPicker207; flCircleColorPicker* colorPicker208;
        flCircleColorPicker* colorPicker209; flCircleColorPicker* colorPicker210; flCircleColorPicker* colorPicker211;
        flCircleColorPicker* colorPicker212; flCircleColorPicker* colorPicker213; flCircleColorPicker* colorPicker214;
        flCircleColorPicker* colorPicker215; flCircleColorPicker* colorPicker216; flCircleColorPicker* colorPicker217;
        flCircleColorPicker* colorPicker218; flCircleColorPicker* colorPicker219;
        //カラーピッカー(300)
        flCircleColorPicker* colorPicker300; flCircleColorPicker* colorPicker301; flCircleColorPicker* colorPicker302;
        flCircleColorPicker* colorPicker303; flCircleColorPicker* colorPicker304; flCircleColorPicker* colorPicker305;
        flCircleColorPicker* colorPicker306; flCircleColorPicker* colorPicker307; flCircleColorPicker* colorPicker308;
        flCircleColorPicker* colorPicker309; flCircleColorPicker* colorPicker310; flCircleColorPicker* colorPicker311;
        flCircleColorPicker* colorPicker312; flCircleColorPicker* colorPicker313; flCircleColorPicker* colorPicker314;
        flCircleColorPicker* colorPicker315; flCircleColorPicker* colorPicker316; flCircleColorPicker* colorPicker317;
        flCircleColorPicker* colorPicker318; flCircleColorPicker* colorPicker319;
        //カラーピッカー(400)
        flCircleColorPicker* colorPicker400; flCircleColorPicker* colorPicker401; flCircleColorPicker* colorPicker402;
        flCircleColorPicker* colorPicker403; flCircleColorPicker* colorPicker404; flCircleColorPicker* colorPicker405;
        flCircleColorPicker* colorPicker406; flCircleColorPicker* colorPicker407; flCircleColorPicker* colorPicker408;
        flCircleColorPicker* colorPicker409; flCircleColorPicker* colorPicker410; flCircleColorPicker* colorPicker411;
        flCircleColorPicker* colorPicker412; flCircleColorPicker* colorPicker413; flCircleColorPicker* colorPicker414;
        flCircleColorPicker* colorPicker415; flCircleColorPicker* colorPicker416; flCircleColorPicker* colorPicker417;
        flCircleColorPicker* colorPicker418; flCircleColorPicker* colorPicker419;
        //カラーピッカー(500)
        flCircleColorPicker* colorPicker500; flCircleColorPicker* colorPicker501; flCircleColorPicker* colorPicker502;
        flCircleColorPicker* colorPicker503; flCircleColorPicker* colorPicker504; flCircleColorPicker* colorPicker505;
        flCircleColorPicker* colorPicker506; flCircleColorPicker* colorPicker507; flCircleColorPicker* colorPicker508;
        flCircleColorPicker* colorPicker509; flCircleColorPicker* colorPicker510; flCircleColorPicker* colorPicker511;
        flCircleColorPicker* colorPicker512; flCircleColorPicker* colorPicker513; flCircleColorPicker* colorPicker514;
        flCircleColorPicker* colorPicker515; flCircleColorPicker* colorPicker516; flCircleColorPicker* colorPicker517;
        flCircleColorPicker* colorPicker518; flCircleColorPicker* colorPicker519;
        //--------------------------------------
        
        //--------------------------------------
        //シンプルラジオボタン(000)
        flRadioButton* radio000; flRadioButton* radio001; flRadioButton* radio002;
        flRadioButton* radio003; flRadioButton* radio004; flRadioButton* radio005;
        flRadioButton* radio006; flRadioButton* radio007; flRadioButton* radio008;
        flRadioButton* radio009;
        flRadioButton* radio010; flRadioButton* radio011; flRadioButton* radio012;
        flRadioButton* radio013; flRadioButton* radio014; flRadioButton* radio015;
        flRadioButton* radio016; flRadioButton* radio017; flRadioButton* radio018;
        flRadioButton* radio019;
        flRadioButton* radio020; flRadioButton* radio021; flRadioButton* radio022;
        flRadioButton* radio023; flRadioButton* radio024; flRadioButton* radio025;
        flRadioButton* radio026; flRadioButton* radio027; flRadioButton* radio028;
        flRadioButton* radio029;
        flRadioButton* radio030; flRadioButton* radio031; flRadioButton* radio032;
        flRadioButton* radio033; flRadioButton* radio034; flRadioButton* radio035;
        flRadioButton* radio036; flRadioButton* radio037; flRadioButton* radio038;
        flRadioButton* radio039;
        //シンプルラジオボタン(100)
        flRadioButton* radio100; flRadioButton* radio101; flRadioButton* radio102;
        flRadioButton* radio103; flRadioButton* radio104; flRadioButton* radio105;
        flRadioButton* radio106; flRadioButton* radio107; flRadioButton* radio108;
        flRadioButton* radio109;
        flRadioButton* radio110; flRadioButton* radio111; flRadioButton* radio112;
        flRadioButton* radio113; flRadioButton* radio114; flRadioButton* radio115;
        flRadioButton* radio116; flRadioButton* radio117; flRadioButton* radio118;
        flRadioButton* radio119;
        flRadioButton* radio120; flRadioButton* radio121; flRadioButton* radio122;
        flRadioButton* radio123; flRadioButton* radio124; flRadioButton* radio125;
        flRadioButton* radio126; flRadioButton* radio127; flRadioButton* radio128;
        flRadioButton* radio129;
        flRadioButton* radio130; flRadioButton* radio131; flRadioButton* radio132;
        flRadioButton* radio133; flRadioButton* radio134; flRadioButton* radio135;
        flRadioButton* radio136; flRadioButton* radio137; flRadioButton* radio138;
        flRadioButton* radio139;
        //シンプルラジオボタン(200)
        flRadioButton* radio200; flRadioButton* radio201; flRadioButton* radio202;
        flRadioButton* radio203; flRadioButton* radio204; flRadioButton* radio205;
        flRadioButton* radio206; flRadioButton* radio207; flRadioButton* radio208;
        flRadioButton* radio209;
        flRadioButton* radio210; flRadioButton* radio211; flRadioButton* radio212;
        flRadioButton* radio213; flRadioButton* radio214; flRadioButton* radio215;
        flRadioButton* radio216; flRadioButton* radio217; flRadioButton* radio218;
        flRadioButton* radio219;
        flRadioButton* radio220; flRadioButton* radio221; flRadioButton* radio222;
        flRadioButton* radio223; flRadioButton* radio224; flRadioButton* radio225;
        flRadioButton* radio226; flRadioButton* radio227; flRadioButton* radio228;
        flRadioButton* radio229;
        flRadioButton* radio230; flRadioButton* radio231; flRadioButton* radio232;
        flRadioButton* radio233; flRadioButton* radio234; flRadioButton* radio235;
        flRadioButton* radio236; flRadioButton* radio237; flRadioButton* radio238;
        flRadioButton* radio239;
        //シンプルラジオボタン(300)
        flRadioButton* radio300; flRadioButton* radio301; flRadioButton* radio302;
        flRadioButton* radio303; flRadioButton* radio304; flRadioButton* radio305;
        flRadioButton* radio306; flRadioButton* radio307; flRadioButton* radio308;
        flRadioButton* radio309;
        flRadioButton* radio310; flRadioButton* radio311; flRadioButton* radio312;
        flRadioButton* radio313; flRadioButton* radio314; flRadioButton* radio315;
        flRadioButton* radio316; flRadioButton* radio317; flRadioButton* radio318;
        flRadioButton* radio319;
        flRadioButton* radio320; flRadioButton* radio321; flRadioButton* radio322;
        flRadioButton* radio323; flRadioButton* radio324; flRadioButton* radio325;
        flRadioButton* radio326; flRadioButton* radio327; flRadioButton* radio328;
        flRadioButton* radio329;
        flRadioButton* radio330; flRadioButton* radio331; flRadioButton* radio332;
        flRadioButton* radio333; flRadioButton* radio334; flRadioButton* radio335;
        flRadioButton* radio336; flRadioButton* radio337; flRadioButton* radio338;
        flRadioButton* radio339;
        //シンプルラジオボタン(400)
        flRadioButton* radio400; flRadioButton* radio401; flRadioButton* radio402;
        flRadioButton* radio403; flRadioButton* radio404; flRadioButton* radio405;
        flRadioButton* radio406; flRadioButton* radio407; flRadioButton* radio408;
        flRadioButton* radio409;
        flRadioButton* radio410; flRadioButton* radio411; flRadioButton* radio412;
        flRadioButton* radio413; flRadioButton* radio414; flRadioButton* radio415;
        flRadioButton* radio416; flRadioButton* radio417; flRadioButton* radio418;
        flRadioButton* radio419;
        flRadioButton* radio420; flRadioButton* radio421; flRadioButton* radio422;
        flRadioButton* radio423; flRadioButton* radio424; flRadioButton* radio425;
        flRadioButton* radio426; flRadioButton* radio427; flRadioButton* radio428;
        flRadioButton* radio429;
        flRadioButton* radio430; flRadioButton* radio431; flRadioButton* radio432;
        flRadioButton* radio433; flRadioButton* radio434; flRadioButton* radio435;
        flRadioButton* radio436; flRadioButton* radio437; flRadioButton* radio438;
        flRadioButton* radio439;
        //シンプルラジオボタン(500)
        flRadioButton* radio500; flRadioButton* radio501; flRadioButton* radio502;
        flRadioButton* radio503; flRadioButton* radio504; flRadioButton* radio505;
        flRadioButton* radio506; flRadioButton* radio507; flRadioButton* radio508;
        flRadioButton* radio509;
        flRadioButton* radio510; flRadioButton* radio511; flRadioButton* radio512;
        flRadioButton* radio513; flRadioButton* radio514; flRadioButton* radio515;
        flRadioButton* radio516; flRadioButton* radio517; flRadioButton* radio518;
        flRadioButton* radio519;
        flRadioButton* radio520; flRadioButton* radio521; flRadioButton* radio522;
        flRadioButton* radio523; flRadioButton* radio524; flRadioButton* radio525;
        flRadioButton* radio526; flRadioButton* radio527; flRadioButton* radio528;
        flRadioButton* radio529;
        flRadioButton* radio530; flRadioButton* radio531; flRadioButton* radio532;
        flRadioButton* radio533; flRadioButton* radio534; flRadioButton* radio535;
        flRadioButton* radio536; flRadioButton* radio537; flRadioButton* radio538;
        flRadioButton* radio539;
        //シンプルラジオボタン(600)
        flRadioButton* radio600; flRadioButton* radio601; flRadioButton* radio602;
        flRadioButton* radio603; flRadioButton* radio604; flRadioButton* radio605;
        flRadioButton* radio606; flRadioButton* radio607; flRadioButton* radio608;
        flRadioButton* radio609;
        flRadioButton* radio610; flRadioButton* radio611; flRadioButton* radio612;
        flRadioButton* radio613; flRadioButton* radio614; flRadioButton* radio615;
        flRadioButton* radio616; flRadioButton* radio617; flRadioButton* radio618;
        flRadioButton* radio619;
        flRadioButton* radio620; flRadioButton* radio621; flRadioButton* radio622;
        flRadioButton* radio623; flRadioButton* radio624; flRadioButton* radio625;
        flRadioButton* radio626; flRadioButton* radio627; flRadioButton* radio628;
        flRadioButton* radio629;
        flRadioButton* radio630; flRadioButton* radio631; flRadioButton* radio632;
        flRadioButton* radio633; flRadioButton* radio634; flRadioButton* radio635;
        flRadioButton* radio636; flRadioButton* radio637; flRadioButton* radio638;
        flRadioButton* radio639;
        //シンプルラジオボタン(700)
        flRadioButton* radio700; flRadioButton* radio701; flRadioButton* radio702;
        flRadioButton* radio703; flRadioButton* radio704; flRadioButton* radio705;
        flRadioButton* radio706; flRadioButton* radio707; flRadioButton* radio708;
        flRadioButton* radio709;
        flRadioButton* radio710; flRadioButton* radio711; flRadioButton* radio712;
        flRadioButton* radio713; flRadioButton* radio714; flRadioButton* radio715;
        flRadioButton* radio716; flRadioButton* radio717; flRadioButton* radio718;
        flRadioButton* radio719;
        flRadioButton* radio720; flRadioButton* radio721; flRadioButton* radio722;
        flRadioButton* radio723; flRadioButton* radio724; flRadioButton* radio725;
        flRadioButton* radio726; flRadioButton* radio727; flRadioButton* radio728;
        flRadioButton* radio729;
        flRadioButton* radio730; flRadioButton* radio731; flRadioButton* radio732;
        flRadioButton* radio733; flRadioButton* radio734; flRadioButton* radio735;
        flRadioButton* radio736; flRadioButton* radio737; flRadioButton* radio738;
        flRadioButton* radio739;
        //--------------------------------------

        
        //--------------------------------------
        //ジョイスティック(000)
        flJoystick* joystick000; flJoystick* joystick001; flJoystick* joystick002; flJoystick* joystick003; flJoystick* joystick004;
        flJoystick* joystick005; flJoystick* joystick006; flJoystick* joystick007; flJoystick* joystick008; flJoystick* joystick009;
        //ジョイスティック(100)
        flJoystick* joystick100; flJoystick* joystick101; flJoystick* joystick102; flJoystick* joystick103; flJoystick* joystick104;
        flJoystick* joystick105; flJoystick* joystick106; flJoystick* joystick107; flJoystick* joystick108; flJoystick* joystick109;
        //ジョイスティック(200)
        flJoystick* joystick200; flJoystick* joystick201; flJoystick* joystick202; flJoystick* joystick203; flJoystick* joystick204;
        flJoystick* joystick205; flJoystick* joystick206; flJoystick* joystick207; flJoystick* joystick208; flJoystick* joystick209;
        //--------------------------------------
        
        //--------------------------------------
        //コンボボックス(000)
        flComboBox* comboBox000; flComboBox* comboBox001; flComboBox* comboBox002; flComboBox* comboBox003;
        flComboBox* comboBox004; flComboBox* comboBox005; flComboBox* comboBox006; flComboBox* comboBox007;
        flComboBox* comboBox008; flComboBox* comboBox009;
        flComboBox* comboBox010; flComboBox* comboBox011; flComboBox* comboBox012; flComboBox* comboBox013;
        flComboBox* comboBox014; flComboBox* comboBox015; flComboBox* comboBox016; flComboBox* comboBox017;
        flComboBox* comboBox018; flComboBox* comboBox019;
        flComboBox* comboBox020; flComboBox* comboBox021; flComboBox* comboBox022; flComboBox* comboBox023;
        flComboBox* comboBox024; flComboBox* comboBox025; flComboBox* comboBox026; flComboBox* comboBox027;
        flComboBox* comboBox028; flComboBox* comboBox029;
        //コンボボックス(100)
        flComboBox* comboBox100; flComboBox* comboBox101; flComboBox* comboBox102; flComboBox* comboBox103;
        flComboBox* comboBox104; flComboBox* comboBox105; flComboBox* comboBox106; flComboBox* comboBox107;
        flComboBox* comboBox108; flComboBox* comboBox109;
        flComboBox* comboBox110; flComboBox* comboBox111; flComboBox* comboBox112; flComboBox* comboBox113;
        flComboBox* comboBox114; flComboBox* comboBox115; flComboBox* comboBox116; flComboBox* comboBox117;
        flComboBox* comboBox118; flComboBox* comboBox119;
        flComboBox* comboBox120; flComboBox* comboBox121; flComboBox* comboBox122; flComboBox* comboBox123;
        flComboBox* comboBox124; flComboBox* comboBox125; flComboBox* comboBox126; flComboBox* comboBox127;
        flComboBox* comboBox128; flComboBox* comboBox129;
        //コンボボックス(200)
        flComboBox* comboBox200; flComboBox* comboBox201; flComboBox* comboBox202; flComboBox* comboBox203;
        flComboBox* comboBox204; flComboBox* comboBox205; flComboBox* comboBox206; flComboBox* comboBox207;
        flComboBox* comboBox208; flComboBox* comboBox209;
        flComboBox* comboBox210; flComboBox* comboBox211; flComboBox* comboBox212; flComboBox* comboBox213;
        flComboBox* comboBox214; flComboBox* comboBox215; flComboBox* comboBox216; flComboBox* comboBox217;
        flComboBox* comboBox218; flComboBox* comboBox219;
        flComboBox* comboBox220; flComboBox* comboBox221; flComboBox* comboBox222; flComboBox* comboBox223;
        flComboBox* comboBox224; flComboBox* comboBox225; flComboBox* comboBox226; flComboBox* comboBox227;
        flComboBox* comboBox228; flComboBox* comboBox229;
        //コンボボックス(300)
        flComboBox* comboBox300; flComboBox* comboBox301; flComboBox* comboBox302; flComboBox* comboBox303;
        flComboBox* comboBox304; flComboBox* comboBox305; flComboBox* comboBox306; flComboBox* comboBox307;
        flComboBox* comboBox308; flComboBox* comboBox309;
        flComboBox* comboBox310; flComboBox* comboBox311; flComboBox* comboBox312; flComboBox* comboBox313;
        flComboBox* comboBox314; flComboBox* comboBox315; flComboBox* comboBox316; flComboBox* comboBox317;
        flComboBox* comboBox318; flComboBox* comboBox319;
        flComboBox* comboBox320; flComboBox* comboBox321; flComboBox* comboBox322; flComboBox* comboBox323;
        flComboBox* comboBox324; flComboBox* comboBox325; flComboBox* comboBox326; flComboBox* comboBox327;
        flComboBox* comboBox328; flComboBox* comboBox329;
        //コンボボックス(400)
        flComboBox* comboBox400; flComboBox* comboBox401; flComboBox* comboBox402; flComboBox* comboBox403;
        flComboBox* comboBox404; flComboBox* comboBox405; flComboBox* comboBox406; flComboBox* comboBox407;
        flComboBox* comboBox408; flComboBox* comboBox409;
        flComboBox* comboBox410; flComboBox* comboBox411; flComboBox* comboBox412; flComboBox* comboBox413;
        flComboBox* comboBox414; flComboBox* comboBox415; flComboBox* comboBox416; flComboBox* comboBox417;
        flComboBox* comboBox418; flComboBox* comboBox419;
        flComboBox* comboBox420; flComboBox* comboBox421; flComboBox* comboBox422; flComboBox* comboBox423;
        flComboBox* comboBox424; flComboBox* comboBox425; flComboBox* comboBox426; flComboBox* comboBox427;
        flComboBox* comboBox428; flComboBox* comboBox429;
        //コンボボックス(500)
        flComboBox* comboBox500; flComboBox* comboBox501; flComboBox* comboBox502; flComboBox* comboBox503;
        flComboBox* comboBox504; flComboBox* comboBox505; flComboBox* comboBox506; flComboBox* comboBox507;
        flComboBox* comboBox508; flComboBox* comboBox509;
        flComboBox* comboBox510; flComboBox* comboBox511; flComboBox* comboBox512; flComboBox* comboBox513;
        flComboBox* comboBox514; flComboBox* comboBox515; flComboBox* comboBox516; flComboBox* comboBox517;
        flComboBox* comboBox518; flComboBox* comboBox519;
        flComboBox* comboBox520; flComboBox* comboBox521; flComboBox* comboBox522; flComboBox* comboBox523;
        flComboBox* comboBox524; flComboBox* comboBox525; flComboBox* comboBox526; flComboBox* comboBox527;
        flComboBox* comboBox528; flComboBox* comboBox529;
        //コンボボックス(600)
        flComboBox* comboBox600; flComboBox* comboBox601; flComboBox* comboBox602; flComboBox* comboBox603;
        flComboBox* comboBox604; flComboBox* comboBox605; flComboBox* comboBox606; flComboBox* comboBox607;
        flComboBox* comboBox608; flComboBox* comboBox609;
        flComboBox* comboBox610; flComboBox* comboBox611; flComboBox* comboBox612; flComboBox* comboBox613;
        flComboBox* comboBox614; flComboBox* comboBox615; flComboBox* comboBox616; flComboBox* comboBox617;
        flComboBox* comboBox618; flComboBox* comboBox619;
        flComboBox* comboBox620; flComboBox* comboBox621; flComboBox* comboBox622; flComboBox* comboBox623;
        flComboBox* comboBox624; flComboBox* comboBox625; flComboBox* comboBox626; flComboBox* comboBox627;
        flComboBox* comboBox628; flComboBox* comboBox629;
        //--------------------------------------
    
    protected:
        int _backWidth;
        int _backHeight;
        int _minBackWidth;
        int _minBackHeight;
        int _normalBackWidth;
        int _normalBackHeight;
    
        bool _isMinimize;
    
        bool _onTop;
    
    private:
        
    public:
        BasicController();
        ~BasicController();
        
        virtual void setup();
        
        virtual void minimize();
        virtual void normalize();
    
    protected:
        virtual void _mouseEventHandler(flEvent& event);
        virtual void _buttonEventHandler(flEvent& event);
    
    private:
};
