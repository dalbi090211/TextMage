#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include "graphic.h"
#include "gameView.h"
#include "character.h"
#include "characterClass.h"
#include "UIConfig.h"
#include "item.h"

using namespace std;

vector<vector<wstring>> story = {
	{//0
		L"게임을 시작합니다.",
		L"용사인 당신은 마을에서 눈을 뜹니다.",
		L"당신의 직업을 선택해주세요 : 1. Mage, 2. Black Mage, 3. Wild Mage"
	},
	{//1
		L"마을에 도착했습니다.",
		L"상점과 던전이 보입니다.",
		L"무엇을 할까요? : 1. 던전, 2. 상점, 3. 인벤토리"
	},
	{//2
		L"숲에 도착했습니다.",
		L"어두컴컴한 숲 속에 작고 귀여운 오크가 보입니다."
	},
	{//3
		L"무엇을 할까요? : 1. 다시 시작"
	},
	{//4
		L"무엇을 할까요? : 1. 다음 스테이지로"
	},
	{//5
		L"무엇을 할까요? : 1. 공격, 2. 할복"
	},
	{//6
		L"어떤 스킬을 사용할까요? : "
	},
	{//7
		L"체력을 회복하였습니다."
	},
	{//8
		L"이름을 입력해주세요 : "
	},
	{//9
		L"이동하려는 곳의 번호를 입력해주세요.",
	},
	{//10
		L"땅이 흔들립니다.",
		L"나무들이 쓰러지는 소리와 함께 거대한 그림자가 드리웁니다.",
		L"눈 앞에 나타난 것은... 전설 속의 오우거.",
		L"3미터는 족히 넘는 거구, 온몸에 새겨진 상처들.",
		L"녀석의 눈이 당신을 향해 고정됩니다.",
	},
	{//11
		L"물건을 구매했습니다.",
	},
	{//12
		L"무엇을 할까요? : 1. 검 구매, 2. 지팡이 구매, 3. 총 구매, 4. 나가기",
	},
	{//13
		L"당신은 상점에 도착했습니다.",
		L"어떤 아이템을 구매할까요?(0 입력 시 종료)",
	},
	{//14
		L"당신은 인벤토리를 열었습니다.",
	},
	{//15
		L"착용하거나 벗으려는 아이템의 번호를 입력해주세요.(0 입력 시 종료)",
	},
	{//16
		L"판매하려는 아이템의 번호를 입력해주세요.(0 입력 시 종료)",
	},
	{//17
		L"숲에 도착했습니다.",
		L"어두컴컴한 숲 속에 작고 귀여운 엘프가 보입니다."
	},
	{//18
		L"던전에 입장했습니다.",
		L"1. 숲, 2. 동굴, 3. 성"
	},
	{//19
		L"동굴에 입장했습니다.",
		L"어두깜깜한 동굴 속에 작고 귀여운 박쥐가 보입니다."
	},
	{//20
		L"동굴에 입장했습니다.",
		L"어두깜깜한 동굴 속에 작고 귀여운 마녀가 보입니다."
	},
	{//21
		L"동굴에 입장했습니다.",
		L"어두깜깜한 동굴 속에 작고 귀여운 토끼 가족이 보입니다."
	},
	{//22
		L"성에 입장했습니다.",
		L"어두깜깜한 성 안에 작고 귀여운 기사가 보입니다."
	},
	{//23
		L"성에 입장했습니다.",
		L"어두깜깜한 성 안에 작고 귀여운 마법사가 보입니다."
	},
	{//24
		L"성에 입장했습니다.",
		L"어두깜깜한 성 안에 작고 귀여운 알파카가 보입니다."
	},
	{//25
		L"수상한 골목에 들어섰습니다.",
		L"담벼락에 기댄 도박꾼이 이쪽을 보며 한판 해보겠냐고 속삭입니다."
	},
	{//26
		L"어두운 골목에 들어섰습니다.",
		L"누군가 주머니를 뒤지는 기척이 느껴집니다.",
		L"재빨리 뒤를 돌아 손을 잡았더니 어린 소녀가 나타났습니다.",
		L"",
		L"1. 빼앗은 물건을 돌려달라고 부탁합니다.",
		L"2. 어린 소녀에게 자비를 베풀어 돈을 쥐어줍니다.",
		L"3. 역으로 돈을 뺐습니다.",
		L"4. 버릇을 고쳐주기로 합니다.",
	},
	{//27
		L"어두운 골목에 들어섰습니다.",
		L"소녀의 두 눈에선 물러설 수 없다는 굳은 의지와",
		L"동생들을 지켜야 한다는 사명감이 묻어나오고 있습니다.",
	} ,
	{//28
		L"도박꾼이 이쪽을 보며 인생을 건 한판 해보겠냐고 속삭입니다.",
		L"",
		L"1. 전재산을 겁니다(확률 : 45%).",
		L"2. 도망칩니다.",
	} ,
	{//29
		L"당신은 길을 걷다가 수상한 노인을 마주쳤습니다.",
		L"그는 자신이 들고 있던 주사기를 흔들며 이렇게 말합니다.",
		L"이 물약을 맞은 사람은 모두 영웅이 되거나 광인이 되어 죽었지.",
		L"자네도 한 번 맞아볼텐가?",
		L"",
		L"1. 물약을 맞는다.(확률 : 50%)",
		L"2. 노인을 공격한다.",
		L"3. 경찰에 신고한다.",
		L"4. 도망간다.",
	} ,
};

vector<wstring> title = {
	{//0
		L"튜토리얼"
	},
	{//1
		L"마을"
	},
	{//2
		L"숲"
	},
	{//3
		L"상점"
	},
	{//4
		L"동굴"
	},
	{//5
		L"성"
	},
};



vector<vector<wstring>> sprite = {
	{//0. 오크
		L"        ,. ─冖'⌒'─､",
		L"       ノ       ＼",
		L"       / ,r‐へへく⌒'￢､  ヽ",
		L"      {ノ へ._、 ,,／~`  〉 ｝",
		L"     ／プ￣￣`y'¨Y´￣￣ヽ─}j=く",
		L"    ノ /レ'>ー{___ｭ`ーー'  ﾘ,ｲ}",
		L"   / _勺 ｲ;；∵r===､､∴'∵;  シ",
		L"  ,/ └'ノ ＼  ご`    ノ{ー—､__",
		L"  人＿_/ー┬ー个-､＿＿,,.. ‐´ 〃`ァーｧー＼",
		L". /  |／ |::::|､      〃 /:::/ ヽ",
		L"/    |  |::::|＼､_________／ /:::/〃  |"
		L"",
		L"",
	},
	{//1. 엘프
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠠⠤⠤⠤⠤⠤⠤⠀⣀⣀⣀⠀⠀⢀⡀⢀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⡒⠉⠀⠀⠀⠒⠲⠤⡀⠀⠀⠀⠈⠙⠻⣷⠿⢄⡀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡔⡵⠋⠀⡆⠀⠀⠀⠀⠀⠀⠈⠳⣄⠀⠀⠀⠀⠀⠑⢄⠙⢪⡓⣌⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢊⠎⠀⠀⢠⠋⠦⡀⠀⠀⠀⠀⠀⠀⠈⢣⡀⢢⠀⠀⠀⠈⢣⡀⢹⣌⢯⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⢃⡎⢀⠀⢠⠇⠀⠀⠈⠒⣵⡲⣖⠖⠀⠀⠠⢣⠈⣇⠀⠀⠀⢰⣵⠀⠘⡆⢻⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⢸⠀⣞⣠⣃⠀⠀⠀⠀⠀⠋⣉⡙⠿⡦⣄⡀⠈⡇⢸⠀⠀⠀⠀⠟⣧⠀⢸⡄⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⡄⢠⢿⠯⠜⠁⠀⠀⠀⠀⢸⡇⠀⠀⠀⡀⠈⠁⢺⠘⠀⠀⠀⠀⢰⢸⠀⢸⣇⠈⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣬⠃⠃⢸⢯⠞⠙⠦⠀⠀⠀⠀⠈⢀⣶⢾⣿⣿⡿⣧⢾⠛⠀⠀⠀⠀⠘⢸⣠⣃⣿⡀⠘⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⠀⢰⢻⠈⢠⣐⣤⣀⠀⠀⠀⠀⠸⠃⠘⡷⢽⠿⠁⢸⣸⡆⠀⠀⠀⣤⢸⢁⣠⠤⠬⠭⠭⠭⣭⣭⠭⢭⡭⠟⣩⠆",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⡀⠀⢻⣠⣿⠻⣟⢿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡿⢧⠀⠀⢠⢿⡏⠙⢢⠀⠀⠀⠀⠀⡼⠨⢔⣯⠴⠋⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⡀⠀⣇⠈⠙⠋⠉⢸⣇⠄⠀⠀⠀⠀⠀⠀⠀⠀⢸⠃⠸⡀⠀⡌⢸⣁⣤⣊⡀⠤⠤⣖⣪⠖⠚⠉⠁⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⢤⣃⣇⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠄⠀⠀⠀⠀⠘⠀⠀⣇⣞⣄⣈⣽⠟⣆⣀⡤⠚⠁⠀⣆⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠯⠭⠝⢻⣿⡄⢸⢧⠀⠀⠀⠀⠀⠒⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⠞⠉⠀⣷⠀⡇⡇⠀⠀⠀⢿⡆⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⢹⣼⠒⠳⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠈⡇⠀⢸⢰⣿⢸⢹⠀⠀⠀⠀⡘⣷⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡌⡼⠈⠀⠀⢿⡷⢄⡀⠀⠀⠀⠀⠀⠀⢀⡠⠔⠉⠀⠀⠀⡇⠀⢸⢸⣿⣏⡇⠀⠀⠀⠀⡇⢋⠇⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣧⠇⠀⠀⠀⣾⡇⠀⡉⡖⢤⣀⣀⣤⣶⣛⣀⣠⣤⣤⣤⣤⣇⠀⢸⡞⣻⡞⠀⠀⠀⠀⠀⣷⢸⡸⡀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡘⠀⠀⠀⢰⠛⠃⣰⢁⣷⡿⣿⣉⣉⡭⠭⠭⠭⠽⠷⠯⠤⠤⡵⢸⣇⣷⠁⠀⠀⠀⠀⠀⢻⢸⡇⢣⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣶⠃⠀⠀⣠⠸⠀⢰⠃⡼⡸⡇⠘⣿⣿⠀⠀⠀⠀⠀⠀⠀⣀⣀⣡⣸⡿⠁⠀⠀⠀⠀⠀⢰⢸⢸⡇⢸⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡇⠀⠀⢀⣇⠇⢠⢃⠜⠹⣹⣁⣈⣉⣉⣉⣉⣉⣉⣉⣉⡁⠤⠤⠤⡼⠁⠀⠀⠀⠀⠀⠆⢸⢸⣾⢣⡎⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀⠀⠀⣜⡜⢠⠟⠁⣀⡀⢀⡏⡜⢡⡏⢸⠀⡇⠀⠀⠀⠀⠀⠀⢰⠃⠀⠀⠀⠀⠀⢰⠀⣸⣰⠷⠃⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡜⠀⠀⠀⢠⠹⢡⠇⠀⠀⠉⠪⣽⣧⡇⠸⡇⠸⠤⡧⠤⠃⠀⠀⠀⠀⡎⠀⠀⠀⠀⠀⠀⠘⠀⣇⠋⠳⣄⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⢀⠔⡽⠀⠀⠀⠀⣎⢀⠏⠀⠀⠀⠀⢠⠃⡘⢀⠏⢹⠀⡄⠁⠀⠀⠀⠀⠀⢰⠃⠀⠀⠀⠀⠀⠀⡇⠀⡏⠀⠀⠘⢷⡄⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⡰⠋⣼⠆⠀⠀⠀⢸⡎⡜⠀⠀⠀⠀⠀⡞⢠⠇⡜⠀⢸⠀⡇⢰⠀⠀⠀⠀⠀⠸⠀⠀⠀⠀⠀⠀⠀⡇⠀⡇⠀⠀⠀⠈⢿⡀⠀⠀",
		L"⠀⠀⠀⠀⢠⠞⠀⡸⡜⠀⠀⠀⠀⠸⢰⠁⠀⠀⠀⠀⣰⠀⡞⢰⡧⢤⢾⠀⡇⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⡇⠀⠀⠀⠀⠈⣿⠀⠀",
		L"⠀⠀⠀⡠⠁⠀⢰⢻⠃⠀⠀⠀⢀⣇⡏⠀⠀⠀⠀⢠⠇⢠⠁⡾⠀⠘⢹⠀⡇⠘⡇⠀⠀⠀⠀⠀⡇⡇⠀⠀⠀⠀⠀⡇⠀⠁⠀⠀⠀⠀⠀⢹⣇⠀",
	},
	{//2. 박쥐
		L"＜￣｀ヽ、　　　　　　　／￣＞",
		L"　ゝ、　　＼　／⌒ヽ,ノ 　/´ ",
		L"　　　ゝ、　`（ ´･ω･)／",
		L"　　 　　>　 　 　,ノ",
		L"　　　　　∠_,,,/´",
		L"",
		L"",
	},
	{//3. 마녀
		L"   /)",
		L"　// ／)",
		L"`/／／／   ____",
		L"｜イ二つ ／⌒⌒ ＼",
		L"｜ 二⊃  (●)　(●) ＼",
		L"/　 ﾉ ／⌒(_人_)⌒ 　＼",
		L"＼_/ ｜　　|┬|　　 ｜",
		L"　/　 ＼　 `ー′　 ／",
		L"",
		L"",
	},
	{//4. 고블린 무리
		L"⠀⠀⠀⠀ (\\__/)⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀ (•ㅅ•)⠀⠀",
		L"⠀＿ ノヽ⠀ノ＼＿⠀",
		L"/⠀️⠀Y⠀⌒Ｙ⌒⠀Ｙ⠀️ヽ",
		L"(   ヽ人⠀⠀/⠀ ⠀ |",
		L"| ﾉ⠀¯¯\\⠀￣￣ヽ ノ",
		L"ヽ＿＿＿⠀＞､＿_／",
		L"⠀⠀⠀｜(⠀王⠀)〈⠀(\\__/)",
		L"⠀⠀⠀/⠀ﾐ`——彡⠀\\ (•ㅅ•)",
		L"",
		L"",
	},
	{//5. 기사
		L" 　/)/) 　 ∧,,∧",
		L".／・　 ﾐ(＾ο＾)",
		L"(＿ノ＼　ﾐ⊂　)",
		L"　　　(　 .しﾉ⌒)～",
		L"　　　 .ＵJ~ＵJ",
		L"",
		L"",
	},
	{//6. 마법사
		L"        *  ✦  *",
		L"      ,──,",
		L"      (･◡･ )  ✦",
		L"      /|   |\\  *",
		L"   ★ /  \\│/  \\ ★",
		L"    /  /─┼─\\  \\",
		L"   |  / ─┼─ \\  |",
		L"   | /   │   \\ |",
		L"   |/    │    \\|",
		L"  (_)   ／|    (_)",
		L"       ／ |",
		L"",
		L"",
	},
	{//7. 알파카
		L"Δ~~~~Δ ",
		L"ξ ･ェ･ ξ ",
		L"ξ　~　ξ ",
		L"ξ　　 ξ ",
		L"ξ　　　\"~～~～〇 ",
		L"ξ　　　　　　 ξ ",
		L"ξ　ξ　ξ~～~ξ　ξ ",
		L"　ξ_ξξ_ξ　ξ_ξξ_ξ ",
		L"",
		L"",
	},
	{//8. 오우거
		L"　　　 ／⌒ヽ",
		L"　　 　/ ^ω^ヽ",
		L"　＿ノ ヽ　ノ ＼＿",
		L"/　`/ ⌒Ｙ⌒ Ｙ　 ヽ",
		L"( 　(三ヽ人　 /　　|",
		L"|　ﾉ⌒＼ ￣￣ヽ　 ノ",
		L"ヽ＿＿＿＞､＿＿_／",
		L"　　 ｜( 王 ﾉ〈",
		L"　　 /ﾐ`ー―彡ヽ",
		L"　　/　ヽ_／　 |",
		L"　 ｜　　/　 ﾉノ",
		L"",
		L"",
	},
	{//9. 소녀
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⠴⠶⠶⠒⠒⠒⠒⠒⠶⠶⣤⣄⡀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⠶⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢶⣄⠀⣠⠴⠚⠛⠳⣦⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠛⠉⠛⣶⠞⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠦⣄⠀⠀⠀⠀⠀⠀⠈⠻⡅⠀⠀⠀⠀⠈⢷⡀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⠁⠈⣹⠞⠁⠀⢀⣴⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⢦⡀⠀⠀⠀⠀⠀⠈⢶⣄⠀⠀⠀⠀⢷⡄",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⣠⠏⠀⢀⠞⠁⠀⠀⣠⠟⠁⠀⠀⠀⠀⠀⠀⣦⠀⠀⡀⠀⠀⠀⠀⠀⠀⡙⢄⠀⠀⠀⠀⠀⢢⢫⠳⡀⠀⠀⠈⣷⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⢠⡏⠀⢠⠏⠀⠀⠀⣴⠋⠀⠀⢀⠆⠀⠀⠀⣼⠋⠳⡄⠙⣦⡀⠀⠀⠀⠀⠈⠈⢣⠀⠀⠀⠀⠀⠀⢧⡱⡀⠀⠀⢸⡇",
		L"⠀⠀⠀⠀⠀⠀⠀⡾⠀⢀⠏⠀⠀⠀⢠⠇⠀⠀⢀⡞⠀⡴⢁⣼⠏⠀⠀⠈⠲⣌⠻⣦⣄⠀⠀⠀⠀⠀⢧⠀⠀⠀⠀⠀⠘⣷⢡⠀⠀⠀⣷",
		L"⠀⠀⠀⠀⠀⠀⢸⠇⠀⡜⠀⠀⠀⠀⡼⠀⠀⣠⡟⣠⠎⣠⠞⠁⠀⠀⠀⠀⠀⠀⣙⡪⢵⡷⣤⣀⠀⠀⢘⡄⠀⠀⠀⠀⠀⠇⢇⡆⠀⠀⢹⡄",
		L"⠀⠀⠀⠀⠀⠀⣼⠀⢀⠃⠀⠀⠀⠀⡇⢀⢴⣯⣞⠷⠛⢳⡄⠀⠀⠀⠀⠀⠀⠘⠤⠤⠤⠚⠋⠛⠻⠴⢆⡇⠀⠀⠀⠀⠀⢸⢸⢰⠀⠀⢸⡇",
		L"⠀⠀⠀⠀⠀⠀⣿⠀⢸⠀⠀⠀⠀⠀⣯⠵⠛⠉⠉⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⢀⡇⠀⢠⢸⣿⠸⠀⠀⠸⡇",
		L"⠀⠀⠀⠀⠀⠀⡇⠀⢸⠀⡀⠀⡆⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⡀⠀⡀⠀⠸⡇⠀⢸⡸⠯⠐⠒⠒⠒⠓⠒⠒⠒⠲⡄",
		L"⠀⢀⣀⣀⣤⣤⡇⠠⢼⠀⡇⠀⣷⠀⢹⠀⢀⣤⣤⣤⣴⣶⣦⠀⠀⠀⠀⠀⠀⠀⠸⠿⠿⠿⠟⠛⠛⠃⠀⡇⢀⠇⠇⠀⡇⡧⠔⢖⢩⠉⠉⠓⠤⠋⣠⠞⠁",
		L"⠐⣯⡉⢠⡔⣒⣢⠤⡬⡆⣿⠀⢣⢇⠘⡄⠈⠋⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡴⡠⠀⢠⢃⠎⡸⠀⡸⣿⠀⠀⣸⡜⠀⠀⣀⡴⠛⠁",
		L"⠀⠀⠙⠲⣌⡀⠀⠱⣣⢣⡏⢧⠈⡎⣆⢣⠰⠡⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡮⠋⢸⠁⣰⣻⣛⡠⠤⠛⣀⠤⠚⣿⠁",
		L"⠀⠀⠀⠀⠀⢹⡗⢤⣉⠫⠧⠼⢧⠘⣟⡿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⣸⡔⢱⡎⣳⡠⠔⠊⠁⠀⠀⢿⠀",
		L"⠀⠀⠀⠀⠀⢸⡇⠀⠈⢹⠒⠴⣅⣱⣽⣧⠀⠀⠀⠀⠀⠀⠀⠀⠦⠤⠔⠤⠤⠖⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣶⠒⢉⠁⠀⠀⠀⠀⠀⠀⢸⡀",
		L"⠀⠀⠀⠀⠀⣿⠀⠀⠀⢸⠀⢠⢄⠀⠀⠈⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠟⠁⣿⠀⡇⡇⠀⠀⠀⠀⠀⠀⢸⡇",
		L"⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⡞⣾⠀⠀⠀⢸⣷⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣟⠁⠀⠀⣿⠀⣟⡇⠀⠀⠀⠀⠀⠀⢸⡇",
		L"⠀⠀⠀⠀⡿⢀⡆⠀⠀⠀⠀⡏⢹⠀⠀⠀⢸⠇⠈⣻⢶⠦⢄⣀⣀⠀⠀⠀⠀⠀⣀⣠⣤⡶⠿⠒⢋⣿⠀⠀⠀⣿⠀⡏⡇⠀⠀⠀⠀⢠⡆⠸⡇",
		L"⠀⠀⠀⣸⠇⣼⠀⠀⠀⠀⠀⠸⠜⠀⠀⠀⣿⣀⣀⣻⡤⡽⢛⡉⠛⠛⠛⠛⠉⣉⣉⣉⠤⠤⠒⠊⡡⣿⡴⠶⢚⠛⠢⡕⠁⠀⠀⢠⠀⢸⢡⠀⣿",
		L"⠀⠀⠀⣿⢰⣿⠀⠀⢀⢀⠀⠀⠀⠀⠀⢠⡿⠋⢉⡙⡧⡇⢸⣴⢶⣯⡉⠉⠀⠀⠀⠀⠀⢀⠤⠊⡠⠟⡦⠖⠁⠀⠀⠘⢆⡀⠀⡈⠀⡌⣸⠀⣿⠀",
		L"⠀⠀⢨⡇⣾⣿⠀⠀⣿⢸⠀⠀⣠⠔⠒⠉⠀⠀⠈⢿⡳⡏⢸⣧⣋⣼⠇⠀⠀⢀⣀⠤⢊⡡⢔⡫⠔⠉⠀⠀⠀⠀⠀⠀⠀⠉⠓⢧⣠⠃⣿⡇⡇",
		L"⠀⠀⢸⡇⣿⣿⠀⠀⠇⡞⡤⠺⡁⠀⠀⠀⠀⠀⠀⠀⠙⠣⢌⡚⠭⠵⠦⠤⢬⣕⡲⠭⠓⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠠⠤⠽⣤⣿⡇⣷",
		L"⠀⠀⢸⡇⣇⢿⡄⠀⢠⣼⠾⣦⡙⢦⡀⠀⠀⠀⢀⡤⣤⠤⠌⠚⠛⠓⠊⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠤⢒⣩⡴⠶⠛⠙⢿⣿⢱⡏",
		L"⠀⠀⠘⣇⣿⠘⢧⣠⡞⠁⠀⠈⠛⢦⣉⠲⠤⣀⡜⢠⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠤⠒⣩⡴⠞⠉⠀⠀⠀⠀⠀⠀⠹⣿⡀",
		L"⠀⠀⠀⠹⣼⣇⣾⠋⠀⠀⠀⠀⠀⠀⠙⠷⡒⠤⢇⡈⠒⠤⢄⣀⡀⠀⠀⠀⠀⠀⠀⢀⣀⡠⠤⠒⣉⣤⠶⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣷⠀",
		L"⠀⠀⠀⠀⢈⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢱⡞⢼⠗⢶⣤⣤⣀⣉⣉⣉⣉⣉⣉⡥⢤⡲⣺⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣧⠀",
		L"⠀⠀⠀⠀⠾⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⣸⠓⢦⢻⡏⠉⠉⠀⠀⠀⠀⠐⠈⠉⣹⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠃",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⣾⠀⣿⠀⠀⠱⣽⣆⠀⠀⠀⠀⠀⠀⠀⠀⢹⠀⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠿⢾⣶⣤⣤⡿⢀⡏⢀⣀⠀⠙⠛⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠈⠀⢀⣀⣄⣀⣤⡄⣤⣶⡯⠟⠋⠉",
		L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠚⠓⠛⠿⠿⠿⠯⠿⠷⠿⠶⠾⠾⠿⠿⠿⠤⠾⠭⠿⠛⠓⠛⠋⠁",
	} ,
};

	//{//2, 엘프(였던것)
	//L"                                                                   ............                                         ",
	//L"                                                            .....::...........:::.......                  ......        ",
	//L"                                                         ..........            .............              ::::::.       ",
	//L"                                                      ...:....................................            :.--::.       ",
	//L"                                                   .....::::::::::::......:::::::::::::::::.....          .....:.       ",
	//L"                                                 ....:::.......::-:.:::..::::...::..:...:..::......                     ",
	//L"                                               ........:......:.:.::.::....:.....:..:..............                     ",
	//L"                                              ..:::::::.:::::....::-:::::::.::.::.::.:::::::::::::..                    ",
	//L"                                             ...........:..:     .:::::........:...:.................                   ",
	//L"                                            .:::::::::.:-:..     .::-:.::.::..:.:.:-:::::::::::::::..                   ",
	//L"                                           .:...........:..       .::-....::......::........:........                   ",
	//L"                                          .-..::::..:..:-::        .::.      ..:.::-::::::::-:::::::...                 ",
	//L"                                         .::......:::   :::           .:..:....::..:.......::.......::                  ",
	//L"                                         .-....::..:.  ..::.         .::.::.....:..:.::..::::.::..::::                  ",
	//L"                                       ..::..:::.:::::::::-.        .::. .:.:....::..::..::::.::.:::.:                  ",
	//L"                                         ::......:.::...:...        ....:::..... .:........::........:.                 ",
	//L"                                        .-..:::::.::. ..::.:.          .::.::::.  :-::::::::-::::::..:.                 ",
	//L"                                        ............  :::....         ...... ......:........::.......:.                 ",
	//L"                                        .::::.:.:.:. ..::.::..                .....-:::::::::..::::::-..                ",
	//L"                                        ::............:....    ..                 .:.......:: ....:..::.                ",
	//L"                                        :::::::::::..          ..                 .::::::::::..::::::::.                ",
	//L"                                        ::.......:--.                             .:.......:::....:..:::                ",
	//L"                                       .::::::.::.:.:..                           .:.::..:::.:::::::::.:...             ",
	//L"                                      .:::::.:::.:::.....         ...            .:-.::::::.........:...::              ",
	//L"                                      .. .::...:.........:.       ...         .....:.....:..       .:   ..              ",
	//L"                                          ::::--:::::-::.=:::....         ....::...:....:..........::.                  ",
	//L"                                         .:...::.....::...:.:....::...:::............................:.                 ",
	//L"                                        .:.:...:.....:....::......:.:::::.........:................:.::.                ",
	//L"                                        .. .:.......::  .:............................ ................::.              ",
	//L"                                            ...::..:.:. .:..........:..:................................:..             ",
	//L"                                               .........::..........:................................... ....           ",
	//L"                                                 .... ....:.........:.. .............  .......................          ",
	//L"                                                  .:................  .........................................         ",
	//L"                                                 ..........    ...... ........... ..............................        ",
	//L"                                                .:.............................................................-        ",
	//L"                                                .. .........................  ..................................        ",
	//}

vector<vector<wstring>> characterInfo = {
	{//1. normal mage
		L"일반적인 위저드입니다.",
		L"높은 능력치를 가지고 있습",
		L"니다.",
	},
	{//2. black mage, 나중에 난이도 한계치 뚫는 아이템 만들면 추가
		L"흑마법사입니다.",
		L"높은 레벨대의 주문만을",
		L"생성합니다.",
	},
	{//3. wild mage
		L"야생학파 위저드입니다.",
		L"가장 높거나 가장 낮은",
		L"난이도의 주문만을",
		L"생성합니다.",
	},
};

int goldCursor = 0;
int curStoryCursor;

int getDisplayWidth( const wstring& str ) {
	int width = 0;
	for ( wchar_t c : str ) {
		if ( (c >= 0x1100 && c <= 0x115F) ||  // 한글 자모
			(c >= 0x2E80 && c <= 0x303E) ||  // CJK 부수
			(c >= 0x3040 && c <= 0x33FF) ||  // 일본어
			(c >= 0xAC00 && c <= 0xD7AF) ||  // 한글
			(c >= 0xFF00 && c <= 0xFF60) ||  // 전각 알파벳
			(c >= 0xFFE0 && c <= 0xFFE6) )    // 전각 기호
			width += 2;
		else
			width += 1;
	}
	return width;
}

void loadCharacterInfo() {
	int tempCursor;
	int maxCursor = 0;
	for ( int i = 0; i < 3; i++ ) {
		tempCursor = curStoryCursor;
		tempCursor++;
		moveCursor( storyStartX + storeInterval * i , storyStartY + tempCursor++ );
		wcout << i + 1 << L". " << CharacterClassToString(i);
		tempCursor++;
		for ( int j = 0; j < characterInfo[ i ].size(); j++ ) {
			moveCursor( storyStartX + storeInterval * i , storyStartY + tempCursor++ );
			wcout << characterInfo[ i ][ j ];
		}
		maxCursor = max( maxCursor , tempCursor );
	}
	curStoryCursor = maxCursor;
}

int getDigitCount( int num ) {
	if ( num == 0 ) return 1;
	int count = 0;
	while ( num > 0 ) {
		num /= 10;
		count++;
	}
	return count;
}


void clearGold() {
	if ( goldCursor == 0 ) return;
	clearArea( graphicMaxX - 1 - goldCursor , graphicMaxY - 8 , goldCursor , 2 );
}

void clearTitle() {
	clearArea( storyStartX, storyStartY-3 , 10 , 1 );
}

void clearInput() {
	clearArea(graphicMinX + 1, graphicMaxY - 1, graphicMaxX - graphicMinX-1, 1);
}

void clearAll() {
	clearArea(graphicMinX + 1, graphicMinY + 1, graphicMaxX - graphicMinX - 1, graphicMaxY - graphicMinY - 1);
	curStoryCursor = 0;
}

//sprite의 x의 최대 길이 구한 후, spriteEndX - 최대 길이 부터 한 줄씩 출력
void drawMonster(int idx) {
	int limitY = graphicMaxY - 8;

	int maxX = 0;
	for ( int line = 0; line < sprite[ idx ].size(); line++ ) {
		int w = getDisplayWidth( sprite[ idx ][ line ] );
		maxX = max( maxX , w );
	}

	for ( int line = 0; line < sprite[ idx ].size(); line++ ) {
		moveCursor( spriteEndX - maxX + 7 , limitY - (sprite[ idx ].size() - line) );
		wcout << sprite[ idx ][ line ];
	}
}

void loadGraphic() {
    // 위쪽 줄
    moveCursor(graphicMinX, graphicMinY);
	wcout << L"┌";
	for ( int x = graphicMinX + 1; x <= graphicMaxX - 1; x++ ) {
        wcout << L"─";
    }
	wcout << L"┐";

    // 아래쪽 줄
    moveCursor(graphicMinX, graphicMaxY);
	wcout << L"└";
    for (int x = graphicMinX+1; x <= graphicMaxX-1; x++) {
        wcout << L"─";
    }
	wcout << L"┘";

    // 좌측 줄
    for (int y = graphicMinY+1; y <= graphicMaxY-1; y++) {
        moveCursor(graphicMinX, y);
        wcout << L"|";
    }

    // 우측 줄
    for (int y = graphicMinY + 1; y <= graphicMaxY - 1; y++) {
        moveCursor(graphicMaxX, y);
        wcout << L"|";
    }
}

void clearScene() {
	system("cls");
	curStoryCursor = 0;
	loadGraphic();
}

void loadStageTitle( int chapter, int stage ) {
	clearTitle();
	moveCursor( storyStartX , storyStartY - 3 );
	wcout << to_wstring( chapter+1 ) << L"-" << to_wstring(stage+1);
	moveCursor( storyStartX , storyStartY - 2 );
	wcout << L"---------";
}

void loadTitle( int idx, int curStage, int curChpater ) {
	clearTitle();
	moveCursor(storyStartX , storyStartY - 3);
	wcout << title[ idx ] << L"(" << to_wstring( curChpater + 1 ) << L"-" << to_wstring(curStage + 1) << L")";
	moveCursor(storyStartX , storyStartY - 2);
	wcout << L"---------";
}

void loadStory(int idx) {
	for (int line = 0; line < story[idx].size(); line++) {
		moveCursor(storyStartX , storyStartY + line + curStoryCursor);
		wcout << story[idx][line];
	}
	curStoryCursor += story[idx].size();
}

void printSkillGet(wstring skillName) {
	moveCursor( storyStartX , storyStartY + curStoryCursor++ );
	wcout << L"\"" << skillName << L"\"스킬을 획득하셨습니다.";
}

void printHeal(int heal) {
	moveCursor( storyStartX , storyStartY + curStoryCursor++ );
	wcout << heal << L"만큼 회복하였습니다.";
}

void printLevelUp(int level) {
	moveCursor(storyStartX , storyStartY + curStoryCursor++);
	wcout << level << L"레벨이 되었습니다.";
}

void printWString(wstring str) {
	moveCursor( storyStartX , storyStartY + curStoryCursor++ );
	wcout << str;
}

void printAllSkillGet( vector<tuple<int , int , wstring>> skills ) {
	moveCursor( storyStartX , storyStartY + curStoryCursor++ );
	wcout << L"현재 생성된 스킬 : ";
	for ( int i = 0; i < (int)skills.size(); i++ ) {
		const auto& [difficulty , damage , name] = skills[ i ];
		moveCursor( storyStartX , storyStartY + curStoryCursor++ );
		wcout << i + 1 << L". " << name
			<< L" (level " << difficulty
			<< L" / 데미지 " << damage << L")";
	}
}

void loadBattle(BattleResult result) {
	if ( result.playerDamage == 0 ) {
		moveCursor( storyStartX , storyStartY + curStoryCursor++ );
		wcout << L"캐스팅 실패! 당신은 주문을 까먹어버렸습니다.";
	}
	else if ( result.playerDamage == -1 ) result.playerDamage = 0;
	moveCursor(storyStartX, storyStartY + curStoryCursor++);
	wcout << L"당신은 " << result.monsterDamage << L"의 피해를 입었습니다.";
	moveCursor(storyStartX, storyStartY + curStoryCursor++);
	wcout << L"적은 " << result.playerDamage << L"의 피해를 입었습니다.";

	if (result.exp < 0) {
		moveCursor(storyStartX, storyStartY + curStoryCursor++);
		wcout << L"몬스터의 공격으로 사망했습니다.";
	}
	else if (result.exp >= 1) {
		moveCursor(storyStartX, storyStartY + curStoryCursor++);
		wcout << L"몬스터를 물리쳤습니다.";
		moveCursor(storyStartX, storyStartY + curStoryCursor++);
		wcout << result.exp << L"의 경험치를 획득했습니다.";
	}
}

void printPleaseInput() {
	clearInput();
	moveCursor(graphicMinX + 1 , graphicMaxY - 2);
	for (int x = graphicMinX + 1; x <= graphicMaxX - 1; x++) {
		wcout << L"─";
	}
    moveCursor(graphicMinX + 1, graphicMaxY - 1);
    wcout << L" >> ";
}

void printGold( int gold ) {
	clearGold();
	int minX = graphicMaxX - 10 - getDigitCount( gold );
	moveCursor(minX, graphicMaxY - 8);
	wcout << L"┌";
	for ( int i = 0; i < 9 + getDigitCount(gold); i++ ) {
		wcout << L"─";
	}
	moveCursor( minX , graphicMaxY - 7 );
	wcout << L"| ";
	wcout << L"gold : " << gold;

	goldCursor = 13 + getDigitCount( gold );
}

void printItemSell(int gold) {
	moveCursor( storyStartX , storyStartY + curStoryCursor++ );
	wcout << gold << L"원을 획득했습니다.";
}

void printItemMoneyList(vector<tuple<wstring , bool, int>> items) {
	int count = 0;
	for ( auto [name , b, gold] : items ) {
		count++;
		moveCursor( storyStartX , storyStartY + curStoryCursor++ );
		wcout << count << L"." << name << ((b == true) ? L"(착용중)" : L"") << L" : " << gold << L"원";
	}
}

void printStore(vector<pair<ItemInfo, int>> items) {
	int tempCursor;
	int maxCursor = 0;
	for ( int t = 0; t < (items.size() - 1) / 2; t++ ) {	//item크기가 0이면 안돌아가는 취약점이 있긴함
		for ( int i = 0; i < 3; i++) {	//현재 창 크기에 띄울 수 있는 최대 아이템 개수의 매직 넘버
			tempCursor = curStoryCursor;
			tempCursor++;
			if ( items[ i + t * 3 ].second == -1 ) {
				moveCursor( storyStartX + storeInterval * i , storyStartY + tempCursor++ );
				wcout << L"입고 예정";
			}
			else {
				moveCursor(storyStartX + storeInterval*i , storyStartY + tempCursor++);
				wcout << i+1 + t * 3 << L". " << ItemNameToString(items[i + t * 3 ].first.name);	//애도 매직 넘버
				tempCursor++;
				moveCursor( storyStartX + storeInterval * i , storyStartY + tempCursor++ );
				wcout << L"가격 : " << items[ i + t * 3 ].first.price;
				tempCursor++;
				moveCursor( storyStartX + storeInterval * i , storyStartY + tempCursor++ );
				wcout << L"효과 : ";
				for ( int j = 0; j < items[i + t * 3 ].first.explain.size(); j++ ) {
					moveCursor( storyStartX + storeInterval * i , storyStartY + tempCursor++ );
					wcout << items[i + t * 3 ].first.explain[j];
				}

				tempCursor++;
				moveCursor( storyStartX + storeInterval * i , storyStartY + tempCursor++ );
				wcout << L"타입 : " << ItemClassToString(items[i+t*3].first.type);
			}
			maxCursor = max(maxCursor, tempCursor);
		}
		curStoryCursor = maxCursor;
		curStoryCursor++;
	}
}

void printEnemyStatusData(int hp, int damage) {
	moveCursor(graphicMaxX - 3 - enemyStatLimitLen * 5 , graphicMaxY - 5 );
	wcout << left << setw( enemyStatLimitLen ) << L"hp : " << setw( enemyStatLimitLen ) << hp;
	wcout << left << setw( enemyStatLimitLen ) << L"power : " << setw( enemyStatLimitLen ) << damage;
}

void printStatusData(const Status& stat, wstring name) {
	for ( int x = graphicMinX + 1; x <= graphicMaxX - 1; x++ ) {
		moveCursor( x , graphicMaxY - 6);
		wcout << L"─";
	}
	
	moveCursor( graphicMinX + 2 , graphicMaxY - 5);
	wcout << L"name : " << name;
	moveCursor(graphicMinX + 10 + name.size()*2, graphicMaxY - 5);	//한국인이면 이름은 한글로
	wcout << L"class : " << CharacterClassToString(stat.type);

    //for (int x = graphicMinX + 1; x <= graphicMaxX - 1; x++) {
    //    moveCursor(x, graphicMaxY - 5);
    //    wcout << "─";
    //}
    moveCursor(graphicMinX + 2, graphicMaxY - 4);
	wcout << left << setw(statLimitLen) << L"level : " << setw(statLimitLen) << stat.level;
	wcout << left << setw(statLimitLen) << L"power : " << setw(statLimitLen) << stat.power;
    moveCursor(graphicMinX + 2, graphicMaxY - 3);
	wcout << left << setw(statLimitLen) << L"hp : " << setw( statLimitLen ) << to_wstring( stat.hp ) + L"/" + to_wstring( stat.maxHp );
	wcout << left << setw(statLimitLen) << L"exp : " << setw( statLimitLen ) << to_wstring( stat.exp ) + L"/" + to_wstring( stat.maxExp );
}

void loadEndingScene() {
	clearAll();

	wstring msg = L"CONGRATULATIONS !!";

	int centerX = graphicMinX + (graphicMaxX - graphicMinX) / 2 - (int)msg.size() / 2;
	int centerY = graphicMinY + (graphicMaxY - graphicMinY) / 3;

	moveCursor( centerX , centerY );
	wcout << msg;

	curStoryCursor = centerY + 6;
	moveCursor( graphicMinX + 4, curStoryCursor++ );
	wcout << L"1. 다시 시작";
	moveCursor( graphicMinX + 4, curStoryCursor++ );
	wcout << L"2. 종료";
}