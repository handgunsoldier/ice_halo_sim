#include <algorithm>
#include <cmath>

#include "core/math.hpp"
#include "gtest/gtest.h"
#include "util/threading_pool.hpp"

namespace {

class RngTest : public ::testing::Test {
 protected:
  static constexpr size_t kCheckSize = 1024;
  static constexpr double kFloatEps = 1e-7;

  static float gaussian_values_[kCheckSize];
  static float uniform_values_[kCheckSize];
};


TEST_F(RngTest, GaussianTest) {
  auto* rng = icehalo::RandomNumberGenerator::GetInstance();
  rng->Reset();
  for (float gaussian_value : gaussian_values_) {
    auto curr_val = rng->GetGaussian();
    ASSERT_NEAR(curr_val, gaussian_value, kFloatEps);
  }
}


TEST_F(RngTest, UniformTest) {
  auto* rng = icehalo::RandomNumberGenerator::GetInstance();
  rng->Reset();
  for (float uniform_value : uniform_values_) {
    auto curr_val = rng->GetUniform();
    ASSERT_NEAR(curr_val, uniform_value, kFloatEps);
  }
}


TEST_F(RngTest, GaussianMultithreadTest) {
  auto* rng = icehalo::RandomNumberGenerator::GetInstance();
  rng->Reset();
  auto thread_pool = icehalo::ThreadingPool::CreatePool();
  thread_pool->CommitRangeStepJobsAndWait(0, kCheckSize, [=](int /* thread_id */, int /* i */) {
    auto curr_val = rng->GetGaussian();
    int match_cnt = 0;
    for (auto v : gaussian_values_) {
      if (std::abs(v - curr_val) < kFloatEps) {
        match_cnt += 1;
      }
    }
    ASSERT_EQ(match_cnt, 1);
  });
}


TEST_F(RngTest, UniformMultithreadTest) {
  auto* rng = icehalo::RandomNumberGenerator::GetInstance();
  rng->Reset();
  auto thread_pool = icehalo::ThreadingPool::CreatePool();
  thread_pool->CommitRangeStepJobsAndWait(0, kCheckSize, [=](int /* thread_id */, int /* i */) {
    auto curr_val = rng->GetUniform();
    int match_cnt = 0;
    for (auto v : uniform_values_) {
      if (std::abs(v - curr_val) < kFloatEps) {
        match_cnt += 1;
      }
    }
    ASSERT_EQ(match_cnt, 1);
  });
}


float RngTest::gaussian_values_[RngTest::kCheckSize]{
  0.15606569f,  0.30639967f,  -0.56803977f, -0.42438623f, -0.80628860f, -0.20454668f, -1.20004416f, -0.42873764f,
  -1.18775189f, 1.30547225f,  -0.15346648f, 0.64747655f,  0.13385749f,  1.19423461f,  -0.75318629f, -1.74047375f,
  1.96709657f,  0.26071024f,  -1.39981210f, -0.26782584f, 0.43909979f,  -0.31403625f, -0.46219131f, 0.03365511f,
  0.25316572f,  0.61478573f,  -2.30282378f, -1.19172311f, 1.68812037f,  -1.99334610f, -0.65231979f, 0.60152262f,
  0.89039135f,  0.63940728f,  -0.27633244f, -0.60309178f, 1.94175375f,  0.18327411f,  0.78793544f,  0.35532930f,
  -0.85567248f, 0.19826457f,  -0.82399011f, 1.79283834f,  0.51870173f,  -0.09992757f, 0.15364595f,  -1.40116668f,
  1.01133049f,  -1.10880303f, -0.42647710f, -0.82731980f, 0.68503261f,  1.04063654f,  1.17471194f,  -0.30703458f,
  1.36774385f,  0.67817360f,  1.03841734f,  -0.84317052f, -1.73056149f, -0.42457297f, 0.67705953f,  -0.65036863f,
  -2.50281453f, -1.47755706f, -0.28589350f, 0.55876362f,  -0.36147115f, -0.64810193f, -1.09106123f, 0.07313449f,
  0.24606876f,  0.57358044f,  -1.05367899f, -0.90364718f, -0.26470137f, 2.65080500f,  -0.63217986f, 0.09329322f,
  1.24464536f,  1.91334867f,  0.57413304f,  -1.53663373f, 0.75447333f,  -1.01593602f, -0.94633549f, 0.07959834f,
  -0.11104874f, 0.58136743f,  1.94201016f,  -0.06933286f, -2.33026481f, 1.10241437f,  0.04773738f,  -0.60462862f,
  0.40093350f,  -0.88128430f, 0.07440522f,  1.46122468f,  0.21652144f,  0.95840591f,  0.91097313f,  0.09210896f,
  -1.10461283f, -0.15850410f, 1.19392562f,  -0.47546953f, -2.30876017f, 0.86699176f,  -1.00929570f, 0.45933521f,
  0.62100756f,  -0.20153503f, -1.89298785f, 0.88297111f,  1.30923617f,  0.71950465f,  0.38076088f,  -0.62958384f,
  0.70695055f,  0.35080379f,  1.25357759f,  1.49763155f,  1.27431488f,  -0.74171442f, -0.70345592f, 1.22548544f,
  -1.32760704f, -0.82786876f, 0.42138734f,  0.26907179f,  -0.18657334f, 0.98942292f,  2.11465025f,  -0.02446533f,
  0.19061011f,  -0.66756302f, -0.32094315f, 0.23905036f,  -0.71173483f, -2.05599999f, 0.11490863f,  0.64767373f,
  -1.32786596f, -1.73742187f, -0.76960158f, 0.76944667f,  0.27661654f,  0.18624565f,  0.64451241f,  -1.73760164f,
  0.35676679f,  -1.05700767f, -1.78988457f, 0.81189197f,  0.01420644f,  -0.25778756f, 0.63478631f,  0.34382710f,
  -2.17520785f, -0.44743389f, 0.27527198f,  0.17828314f,  2.25968385f,  -0.59729385f, 1.86055815f,  0.50023371f,
  -1.29024076f, -0.10838633f, -0.61218375f, 0.40956551f,  1.88360143f,  -0.34154820f, 1.63745010f,  0.05286462f,
  0.66658711f,  -0.76519418f, 1.84342134f,  0.16437985f,  -0.08061321f, -0.07031316f, -0.26067683f, -0.05629579f,
  -0.48181874f, 0.01002085f,  -0.25859737f, -0.40540293f, 0.73274344f,  -0.43000999f, 0.22422281f,  -1.54891157f,
  0.05521702f,  0.48887265f,  0.75868946f,  -0.49173090f, -0.46713465f, -0.33109450f, -0.25883022f, -0.47875783f,
  1.90155602f,  1.55359995f,  0.43024558f,  -0.07519604f, 0.93145007f,  -2.01699162f, 0.91202885f,  -0.63780481f,
  -0.94726759f, 0.77119172f,  1.22224069f,  0.44951954f,  -1.92345691f, -1.25367045f, 0.57583451f,  0.39895585f,
  1.56409442f,  -0.45689183f, 1.61199689f,  -2.05275273f, -0.93727803f, -0.35603300f, -0.29954726f, 0.21518119f,
  -1.32482994f, 0.56187141f,  0.75898272f,  1.96140242f,  -0.40943798f, -0.19671024f, 0.30418384f,  -0.09060571f,
  0.50211489f,  -1.66157520f, -0.46074432f, -0.64712352f, 0.49789497f,  -0.69097853f, 1.16379571f,  -1.84336078f,
  0.67494518f,  0.46891081f,  -1.02347493f, -0.79201978f, -0.03053894f, -1.44914341f, 0.04069660f,  0.16344246f,
  -0.61883181f, 0.46762607f,  -0.05925406f, 1.36203623f,  0.56583810f,  1.39729762f,  2.25449252f,  -1.46424484f,
  -1.96255612f, 0.34199512f,  0.24890621f,  -1.10482645f, -2.38158607f, 0.17463210f,  0.26126051f,  -1.45813501f,
  0.18689775f,  0.31725016f,  2.00847173f,  -0.44917747f, -0.39716247f, -0.62127513f, -0.55965674f, -1.23749781f,
  0.19886617f,  -0.65269202f, -0.07944115f, -0.11089539f, 0.49383834f,  -0.65998882f, -0.57203746f, -0.18942346f,
  -0.25201184f, -0.42550540f, 0.32763034f,  -0.38351473f, 1.87589550f,  1.03013849f,  0.08979345f,  1.23621976f,
  0.67235285f,  0.19513708f,  -1.16832209f, -0.86614835f, -0.24801627f, 0.13028924f,  1.72410369f,  0.16676287f,
  0.86195105f,  0.74994981f,  0.45073467f,  0.19518310f,  -0.25853744f, -0.03893057f, -0.90386349f, 0.77769279f,
  0.62809211f,  1.37869895f,  0.55907261f,  -0.12748472f, 0.26666099f,  -1.39554751f, 0.20621026f,  0.62103724f,
  -0.82457536f, -1.54047799f, -0.05352015f, -1.27235246f, 0.06896876f,  -0.31465784f, 2.02170229f,  -1.95847762f,
  0.68861473f,  -0.21645667f, -1.51527333f, 1.57412016f,  -1.06012130f, -0.47283682f, -0.77330637f, 0.40938014f,
  0.00372434f,  -0.32051909f, -0.40077490f, -0.03388521f, 0.99315828f,  -0.50343180f, -0.33911118f, -0.01951999f,
  -2.08852983f, 0.03825319f,  1.36788487f,  0.15194073f,  -0.91460443f, -1.28724742f, 0.52277827f,  -0.17273046f,
  0.18641515f,  0.90072984f,  0.48549080f,  -0.33129367f, -1.34259045f, -2.34359503f, 0.61537838f,  -2.04093146f,
  1.34620595f,  0.34744686f,  -0.38480833f, -0.67068827f, -0.01403390f, 0.64801401f,  0.87192553f,  -1.63976371f,
  0.45517275f,  -1.37117863f, -0.41282937f, -1.56420755f, 0.28468469f,  0.33696193f,  -0.75707924f, -1.08480227f,
  2.28597379f,  1.28887093f,  -0.50332594f, -0.49177760f, 1.36000371f,  0.41962624f,  0.12860589f,  -0.51871520f,
  -0.10427364f, -0.58834022f, 1.64478433f,  -0.92389131f, 0.78950930f,  0.14504568f,  -0.69589525f, -1.38309550f,
  0.33835173f,  -1.10583591f, 0.54166472f,  -0.47851446f, 1.64381027f,  -1.81775212f, 1.23549092f,  -1.46926284f,
  -1.06900740f, 0.99652004f,  0.73793298f,  1.67848802f,  0.11749950f,  -0.19986153f, 0.67349720f,  0.76410669f,
  0.29727769f,  0.60118079f,  -0.87306380f, -1.16098988f, 2.01899099f,  -0.38565138f, -0.72870803f, -2.07940674f,
  -0.61913711f, -1.36424661f, -0.06395616f, -0.34193027f, -2.38970447f, 0.76813978f,  -0.38855559f, -0.78684157f,
  2.03472161f,  1.02569270f,  -0.25581992f, -1.21823919f, 0.39521962f,  -0.06583510f, 1.13369620f,  1.17760932f,
  -0.85095155f, -0.63829017f, -0.02828304f, -0.18907078f, -0.64992738f, -1.16222262f, 0.20007895f,  0.13975932f,
  2.10129642f,  0.22720143f,  -1.04035389f, -0.84527791f, 1.15216303f,  0.13219438f,  0.08766305f,  1.13833177f,
  0.51071817f,  -0.53222549f, 0.14053632f,  -0.80739462f, 0.93583173f,  -2.76600695f, 0.11389206f,  -0.71613520f,
  -0.14931256f, 1.35757422f,  -1.41509974f, 1.22600901f,  -0.87655711f, 1.47688663f,  -0.16630612f, -0.10356762f,
  -0.83719790f, -0.57528943f, 0.26143327f,  0.30605713f,  1.27764595f,  1.08722401f,  0.28967479f,  -1.30310512f,
  -1.24049234f, 0.08154578f,  -0.07493218f, 0.91375536f,  -2.12646580f, -0.34126183f, -0.43312502f, 0.54663956f,
  0.31315869f,  1.14678991f,  -0.41973844f, -0.80651945f, 0.84110910f,  0.08143181f,  0.88286901f,  -0.07093956f,
  -0.71184731f, -0.82449532f, -0.96728331f, -0.14709458f, -1.39080572f, -0.08933508f, -0.00522797f, -2.09600401f,
  -1.46718287f, 0.02747249f,  -1.15609419f, 0.79444921f,  -0.28207478f, -1.14779198f, 1.59919965f,  1.44046760f,
  -1.09816849f, -0.74539047f, 0.08028393f,  1.47015607f,  -0.12153354f, -1.50196028f, -0.44389510f, -0.38314107f,
  1.02036190f,  1.51153374f,  0.15373993f,  -1.20093334f, 2.16261578f,  0.14536965f,  0.43007016f,  -0.60751694f,
  0.04588025f,  0.94611967f,  0.92484981f,  0.69803822f,  -1.60947084f, -0.98105186f, 0.98542088f,  -0.42274052f,
  0.95739013f,  0.32546994f,  1.11727214f,  0.42824960f,  0.85966444f,  -0.43345046f, 0.88103938f,  1.30064487f,
  0.79724836f,  1.01558244f,  1.69705129f,  -1.44235516f, 0.93636191f,  0.63859075f,  -0.46180013f, 0.08469372f,
  1.07836533f,  -0.91266549f, -1.11498678f, -0.86416519f, -0.74231195f, -0.83583838f, 1.11190176f,  1.44833195f,
  -0.65042764f, 1.17269397f,  1.44277930f,  0.06159383f,  -0.99041986f, 2.11982703f,  0.22873624f,  -0.02513701f,
  -0.95798814f, -0.37686768f, 0.91025281f,  0.12255640f,  1.08411276f,  -2.31239629f, 0.54497349f,  -1.18462932f,
  0.58422470f,  2.01881695f,  0.11771775f,  1.37682354f,  -1.10510707f, -0.12685496f, -0.30467331f, 0.81778693f,
  -0.45184791f, 0.03236338f,  -1.17265642f, 0.26684615f,  0.18056926f,  0.30690533f,  -0.81576294f, 1.38228381f,
  0.35503238f,  0.29907477f,  1.93723392f,  -0.20045266f, 1.95598984f,  -0.12728675f, -0.37853959f, 0.41506901f,
  -1.95480633f, 1.86839104f,  0.56578076f,  -1.59598994f, 0.28515568f,  -0.00771900f, -0.86961251f, -0.65832937f,
  -0.73278266f, -0.79768264f, -1.29818559f, 0.80106074f,  0.14638019f,  0.24641249f,  -0.20151922f, -1.40291858f,
  0.78724444f,  -3.16074419f, -0.88233799f, 0.68917030f,  0.96550900f,  -0.63739723f, -1.89623046f, -0.10285117f,
  0.18259904f,  -0.80398506f, 0.29286677f,  -0.28474954f, -2.39532351f, 0.06032412f,  0.68399614f,  0.78726339f,
  0.02551857f,  0.92441428f,  0.21768956f,  -1.49094045f, 0.78508347f,  -0.62555718f, -0.47509885f, 0.06522772f,
  0.40476048f,  -0.71053976f, -0.60806912f, -2.22236705f, -1.52903938f, 0.03143088f,  -1.08527052f, 0.90579087f,
  -0.82657975f, -0.08496770f, -0.98754102f, -1.91922998f, 0.13191871f,  -0.44784677f, 1.23952746f,  -0.45893532f,
  1.86757302f,  -0.39360160f, 0.87418169f,  0.77409428f,  -0.25921449f, 0.67398673f,  0.74323058f,  -0.47835293f,
  -0.28645536f, 1.27790129f,  1.03354466f,  0.49862495f,  -0.66191351f, 0.43688688f,  -0.73003000f, 0.17920268f,
  -0.69364911f, 0.13441499f,  -1.30935442f, 2.32433200f,  -0.83390743f, -0.29974434f, -1.47842348f, -1.58689904f,
  0.50401926f,  0.68616778f,  -0.03488215f, 0.35335857f,  -1.28532207f, 2.19793391f,  -0.26264146f, 2.04737496f,
  -0.05429080f, -0.86407185f, -0.47735032f, 1.36689818f,  -0.29853141f, 0.09910856f,  -0.65074015f, 0.38083875f,
  0.95971924f,  1.52335799f,  0.09444837f,  -0.96286130f, 1.44644213f,  0.05180071f,  0.45677376f,  0.23726420f,
  -1.08094096f, 0.36414847f,  -0.39161605f, 0.42350453f,  0.93107319f,  1.48980820f,  0.88542789f,  0.12013298f,
  0.86035836f,  0.99972510f,  0.90311879f,  -0.91734058f, -1.89743137f, 1.41134346f,  -1.30567884f, 0.72583181f,
  -1.30390847f, -0.04112681f, 0.20113800f,  0.24096514f,  -0.13252121f, 0.13048854f,  -1.29770112f, 0.81331927f,
  1.24354243f,  0.33351403f,  -0.96982646f, -1.11833441f, -0.64433914f, 0.82740134f,  3.28082609f,  0.15951207f,
  -0.72718614f, 1.06732464f,  -0.21284840f, 0.67154324f,  -0.08339548f, -0.57159913f, 0.07068007f,  -1.56045926f,
  1.82025826f,  -0.13158880f, 0.78592956f,  0.30160058f,  0.21869157f,  -1.92597890f, -0.33249667f, 0.73932314f,
  2.81337905f,  0.73159117f,  0.90208131f,  -1.10449624f, -0.12686995f, 1.02349401f,  2.33212972f,  -0.03665518f,
  -1.23735821f, -0.98185903f, 0.35311198f,  -1.35951149f, -0.55494374f, 0.94063723f,  0.06338762f,  1.24384081f,
  0.85066861f,  0.04656964f,  -0.25793895f, -1.18597925f, -0.16412044f, -0.56177080f, 0.68499613f,  0.11656944f,
  1.05827701f,  -0.37235671f, 0.65846765f,  0.22079991f,  -0.33615050f, -0.45980519f, -0.79809982f, -0.18050233f,
  -1.23103166f, -0.64822161f, -0.45575449f, -0.85650420f, -0.25409803f, 0.27850434f,  0.22843879f,  -0.84894347f,
  -0.10635876f, 0.55770612f,  0.40050828f,  -0.42182133f, -1.30904591f, -0.25192139f, 0.49604213f,  -0.83440995f,
  -0.32779562f, 0.47882268f,  2.62446165f,  -0.76201683f, -1.67388713f, -1.11782753f, -0.14554177f, -0.07376035f,
  0.39766398f,  -0.87549025f, -0.01509155f, 1.52916646f,  0.07808788f,  -1.32205367f, -1.22226834f, 0.31352776f,
  0.12270820f,  0.74289298f,  1.31977558f,  -0.19725995f, 0.30746388f,  -1.12076855f, 0.33205923f,  0.21840878f,
  1.28838289f,  1.71036088f,  -0.13041495f, 1.02581406f,  -1.03342438f, -1.49457943f, 0.32077494f,  0.07050505f,
  0.39550564f,  -0.07044325f, 0.60633552f,  -0.68937969f, 0.37264904f,  -0.38383603f, 1.46370804f,  1.37752128f,
  0.16197118f,  -0.42592579f, -0.27533087f, -2.04193234f, -0.66079652f, 1.22093916f,  -0.04014840f, -1.47194171f,
  1.58214867f,  0.58641583f,  -1.30582356f, -2.50628018f, -0.83600426f, 2.22870231f,  -0.82413530f, -0.40947455f,
  1.08656776f,  -0.78664112f, -1.49943256f, -0.19873342f, -1.42360783f, 1.19611228f,  0.02837565f,  -0.54968786f,
  0.84188259f,  -0.81491196f, -0.10568756f, 1.08258057f,  0.04687965f,  1.96800172f,  0.37848872f,  0.80787790f,
  1.23430336f,  -0.66017640f, -0.99068558f, -0.27657431f, 0.03354292f,  0.75982261f,  1.34781730f,  -0.21409810f,
  1.05456281f,  1.21028185f,  0.80629867f,  1.09462953f,  -1.41813004f, 2.17314482f,  0.52778268f,  1.12494457f,
  -0.19834557f, -2.09520411f, 1.10422492f,  0.19779931f,  1.10902989f,  0.41148475f,  2.08418560f,  -0.58547074f,
  0.56149912f,  1.01133871f,  0.47623906f,  -1.52724230f, -1.62718201f, -0.55637538f, 0.26725844f,  1.34936702f,
  1.95533133f,  0.54793364f,  -0.73913258f, -1.26455843f, -0.74201846f, -0.61577958f, 0.83390182f,  -0.84337479f,
  -1.50060332f, 0.82565194f,  0.85468727f,  -0.74314439f, -2.60007596f, 0.87346870f,  1.20066106f,  -0.46725252f,
  -0.09968653f, -0.31574488f, -0.42746806f, 0.51301891f,  1.53421497f,  -0.28719339f, 0.50287402f,  -0.69301504f,
  -0.54207647f, -0.61757398f, -1.46624982f, 0.21177980f,  -0.84726250f, -0.63970226f, -1.15797734f, -0.02180581f,
  -0.74282354f, 1.41378140f,  1.27425897f,  1.16840625f,  0.98867196f,  0.62687409f,  -1.07415020f, 0.74367863f,
  -1.30770159f, 0.45534006f,  0.63896585f,  0.23725602f,  1.84585488f,  0.15455948f,  0.09355123f,  -0.74743491f,
  -1.91195464f, -0.25589189f, 1.26340508f,  -0.05756177f, -1.10253561f, 2.00926137f,  -0.03865188f, -0.76011914f,
  -0.92719340f, -0.30787417f, -1.14018393f, -0.31128350f, -2.47815561f, 1.17671442f,  -2.14927649f, -1.20230937f,
  -0.88533604f, -0.42902502f, 1.26977146f,  -0.86343324f, 2.05073857f,  -0.73242372f, 0.23293373f,  0.36934298f,
  -0.25209573f, 0.33241361f,  0.39747319f,  1.23215747f,  1.00246966f,  -1.40304554f, 0.15935874f,  0.70266616f,
  -0.03817602f, -0.08494543f, 1.34162891f,  -0.81021076f, -0.13191159f, 0.75389177f,  1.13696778f,  -0.65263659f,
  0.68081820f,  0.50587958f,  -1.37602139f, -0.15277998f, -0.18826024f, -0.74956191f, -0.63417625f, -0.95176107f,
  -0.82830471f, 1.40960717f,  1.47011423f,  -2.50527978f, -0.21015272f, 2.73056436f,  -0.36071247f, -0.29274961f,
  -0.88865858f, 0.66757911f,  0.32307601f,  2.79589462f,  -1.47195065f, 0.65706348f,  -0.27109423f, 0.75914997f,
  1.32945919f,  0.46409333f,  -0.28081247f, 0.20273118f,  0.69243735f,  1.78417444f,  -1.36654377f, 0.13849868f,
  0.82850164f,  2.49702239f,  1.43886888f,  -0.67945093f, -0.67223400f, -0.45844999f, 1.97675860f,  -1.96117246f,
  -1.46793592f, 0.24652591f,  0.45759630f,  0.61070818f,  0.58510882f,  0.82890087f,  -0.75152940f, -0.55469602f,
};

float RngTest::uniform_values_[RngTest::kCheckSize]{
  0.41702199f, 0.99718481f, 0.72032452f, 0.93255734f, 0.00011438f, 0.12812445f, 0.30233258f, 0.99904054f, 0.14675589f,
  0.23608898f, 0.09233859f, 0.39658073f, 0.18626021f, 0.38791075f, 0.34556073f, 0.66974604f, 0.39676747f, 0.93553907f,
  0.53881675f, 0.84631091f, 0.41919452f, 0.31327352f, 0.68521953f, 0.52454817f, 0.20445225f, 0.44345289f, 0.87811744f,
  0.22957721f, 0.02738760f, 0.53441393f, 0.67046750f, 0.91396201f, 0.41730481f, 0.45720482f, 0.55868983f, 0.43069857f,
  0.14038694f, 0.93912780f, 0.19810149f, 0.77838922f, 0.80074459f, 0.71597052f, 0.96826160f, 0.80275750f, 0.31342417f,
  0.09280081f, 0.69232261f, 0.51815253f, 0.87638915f, 0.86502028f, 0.89460665f, 0.82914692f, 0.08504421f, 0.82960337f,
  0.03905478f, 0.27304998f, 0.16983043f, 0.05924320f, 0.87814248f, 0.67052805f, 0.09834684f, 0.59306550f, 0.42110762f,
  0.67165411f, 0.95788956f, 0.41178787f, 0.53316528f, 0.19755089f, 0.69187713f, 0.28962964f, 0.31551564f, 0.14212014f,
  0.68650091f, 0.78331447f, 0.83462566f, 0.41253886f, 0.01828828f, 0.03417131f, 0.75014430f, 0.62402999f, 0.98886108f,
  0.66063571f, 0.74816567f, 0.29849529f, 0.28044400f, 0.44613451f, 0.78927934f, 0.22212455f, 0.10322601f, 0.07336418f,
  0.44789353f, 0.46923852f, 0.90859550f, 0.09617226f, 0.29361415f, 0.90337014f, 0.28777534f, 0.11949047f, 0.13002858f,
  0.52479941f, 0.01936696f, 0.08362301f, 0.67883551f, 0.91686136f, 0.21162811f, 0.91044837f, 0.26554665f, 0.29893011f,
  0.49157315f, 0.58438915f, 0.05336254f, 0.56591201f, 0.57411760f, 0.61393833f, 0.14672858f, 0.95653564f, 0.58930552f,
  0.26097897f, 0.69975835f, 0.23101541f, 0.10233443f, 0.53344852f, 0.41405597f, 0.94993812f, 0.69440013f, 0.49305961f,
  0.41417927f, 0.54060054f, 0.04995346f, 0.76548511f, 0.53589642f, 0.04534572f, 0.66379464f, 0.13996612f, 0.51488912f,
  0.79240358f, 0.94459474f, 0.02980136f, 0.58655506f, 0.88312548f, 0.90340191f, 0.54078817f, 0.13747470f, 0.44798020f,
  0.13927634f, 0.89213586f, 0.80739129f, 0.37758434f, 0.39767683f, 0.53842467f, 0.16535419f, 0.65229887f, 0.92750859f,
  0.36126101f, 0.34776586f, 0.57100856f, 0.75081211f, 0.63783646f, 0.72599798f, 0.12631488f, 0.88330609f, 0.69020456f,
  0.62367219f, 0.64774942f, 0.75094241f, 0.35393909f, 0.34889835f, 0.76323307f, 0.26992789f, 0.35653171f, 0.89588624f,
  0.75278836f, 0.42809120f, 0.88134181f, 0.96484005f, 0.01166919f, 0.66344148f, 0.49810907f, 0.62169570f, 0.07379201f,
  0.11474597f, 0.78695148f, 0.94948924f, 0.06406733f, 0.44991213f, 0.35531035f, 0.57838959f, 0.94183695f, 0.40813681f,
  0.37980330f, 0.23702697f, 0.76292008f, 0.90337950f, 0.77159500f, 0.57367951f, 0.30136049f, 0.00287032f, 0.77273917f,
  0.61714494f, 0.15292983f, 0.32664490f, 0.57863390f, 0.52705812f, 0.00900800f, 0.88594210f, 0.70904255f, 0.35726976f,
  0.47064081f, 0.90853512f, 0.76459259f, 0.62336010f, 0.46739268f, 0.01582124f, 0.26900104f, 0.92943722f, 0.83169258f,
  0.69089693f, 0.55132496f, 0.99732286f, 0.07008149f, 0.17234051f, 0.47247505f, 0.13713574f, 0.74276483f, 0.93259549f,
  0.19195607f, 0.69681817f, 0.46431151f, 0.06600017f, 0.23036280f, 0.75546306f, 0.50824755f, 0.75387621f, 0.20856830f,
  0.92302454f, 0.04930425f, 0.71152478f, 0.51886189f, 0.12427096f, 0.17227836f, 0.01988013f, 0.39631328f, 0.02621099f,
  0.10736531f, 0.02830649f, 0.50981027f, 0.24621107f, 0.10213523f, 0.86002797f, 0.28871784f, 0.53883106f, 0.23175846f,
  0.55282199f, 0.96766794f, 0.84203088f, 0.27831885f, 0.12417331f, 0.23362252f, 0.27918369f, 0.09155644f, 0.58575928f,
  0.57006663f, 0.96959573f, 0.41792655f, 0.56103021f, 0.36784324f, 0.01864729f, 0.81299496f, 0.80063266f, 0.28975999f,
  0.23297428f, 0.71739161f, 0.80710518f, 0.61294812f, 0.38786066f, 0.42690983f, 0.86354184f, 0.75187296f, 0.74712163f,
  0.42781264f, 0.55624026f, 0.42838240f, 0.13645522f, 0.36190444f, 0.05991770f, 0.15333848f, 0.12134345f, 0.93719035f,
  0.04455188f, 0.91640985f, 0.10749412f, 0.78195846f, 0.22570933f, 0.61632895f, 0.71298897f, 0.03599944f, 0.55971700f,
  0.65432376f, 0.01255598f, 0.12976961f, 0.07197428f, 0.29435948f, 0.96727633f, 0.36081475f, 0.56810045f, 0.27464515f,
  0.20329323f, 0.07396900f, 0.25232574f, 0.15213716f, 0.74382585f, 0.16161853f, 0.19542947f, 0.93871170f, 0.58135891f,
  0.37113389f, 0.97002000f, 0.05001808f, 0.84682882f, 0.74095553f, 0.23984776f, 0.29868025f, 0.49376971f, 0.20435813f,
  0.61995572f, 0.98175663f, 0.82898092f, 0.89302123f, 0.15679139f, 0.75934881f, 0.01857620f, 0.65112054f, 0.07002214f,
  0.03968350f, 0.48634511f, 0.81387639f, 0.60632944f, 0.76257312f, 0.56885141f, 0.45528248f, 0.31736240f, 0.53182644f,
  0.98861617f, 0.10933606f, 0.57974523f, 0.14603275f, 0.38014117f, 0.50878876f, 0.55094820f, 0.21565028f, 0.74533445f,
  0.91644371f, 0.66923290f, 0.46215251f, 0.26491955f, 0.13226728f, 0.06633484f, 0.76424164f, 0.37008420f, 0.21273370f,
  0.62971753f, 0.07425843f, 0.21017401f, 0.09541924f, 0.75275558f, 0.16220552f, 0.06653649f, 0.35646367f, 0.26031509f,
  0.09530781f, 0.80475456f, 0.14326301f, 0.19343428f, 0.93101293f, 0.63946086f, 0.57658422f, 0.52467030f, 0.83964521f,
  0.92480797f, 0.62329209f, 0.26329678f, 0.32451749f, 0.06596109f, 0.72801167f, 0.73506594f, 0.52273661f, 0.77217805f,
  0.73681146f, 0.90781587f, 0.16540611f, 0.93197209f, 0.68705827f, 0.01395157f, 0.42681083f, 0.23436208f, 0.72855741f,
  0.61677837f, 0.75633538f, 0.94901633f, 0.39761129f, 0.95017612f, 0.92520010f, 0.55665320f, 0.20351031f, 0.91560638f,
  0.00800271f, 0.64156622f, 0.92635071f, 0.39000770f, 0.29451156f, 0.48599067f, 0.16695160f, 0.60431051f, 0.02410163f,
  0.54954791f, 0.45200160f, 0.92618144f, 0.80833876f, 0.91873342f, 0.36837685f, 0.39487562f, 0.60920697f, 0.96326256f,
  0.03484773f, 0.17395566f, 0.35457724f, 0.12632953f, 0.07851997f, 0.13507916f, 0.69318521f, 0.50566214f, 0.01271267f,
  0.02152481f, 0.45954528f, 0.94797021f, 0.96131724f, 0.82711548f, 0.33418521f, 0.01501898f, 0.47208342f, 0.17619626f,
  0.10539125f, 0.33206359f, 0.50307590f, 0.13099684f, 0.88568985f, 0.80949068f, 0.53437734f, 0.34473667f, 0.28147677f,
  0.94010746f, 0.35458469f, 0.58201420f, 0.89628023f, 0.87883198f, 0.24148914f, 0.84473443f, 0.02388409f, 0.90539229f,
  0.96572679f, 0.45988026f, 0.42996791f, 0.54634684f, 0.34628850f, 0.79860359f, 0.57706761f, 0.28571886f, 0.12652616f,
  0.49025351f, 0.95004332f, 0.59911031f, 0.31361082f, 0.01553327f, 0.95283115f, 0.59348142f, 0.21839324f, 0.43367636f,
  0.24870020f, 0.80736053f, 0.86380178f, 0.31524479f, 0.23526832f, 0.89288872f, 0.81510007f, 0.57785720f, 0.54389721f,
  0.18401021f, 0.19126026f, 0.78792924f, 0.58883995f, 0.61203116f, 0.04813680f, 0.05390928f, 0.01587298f, 0.42019367f,
  0.04971102f, 0.67906886f, 0.39941528f, 0.91860175f, 0.57690394f, 0.00040202f, 0.86751747f, 0.97675914f, 0.78616226f,
  0.37658033f, 0.25470275f, 0.97378355f, 0.08225491f, 0.60471612f, 0.15775600f, 0.82884580f, 0.20949288f, 0.57471150f,
  0.41738281f, 0.62807620f, 0.34769002f, 0.28557628f, 0.69988406f, 0.58683336f, 0.69750947f, 0.75002176f, 0.07472389f,
  0.85831386f, 0.03646970f, 0.75508219f, 0.78939986f, 0.69805723f, 0.90052855f, 0.86447942f, 0.00466331f, 0.32268101f,
  0.26420331f, 0.67078876f, 0.46737731f, 0.45087394f, 0.35981619f, 0.38210276f, 0.24021763f, 0.41081136f, 0.02316873f,
  0.40147957f, 0.53166813f, 0.31738394f, 0.13019472f, 0.62191939f, 0.56145895f, 0.43024728f, 0.16783080f, 0.97380209f,
  0.42107475f, 0.67780089f, 0.68468791f, 0.19856989f, 0.27390033f, 0.42670101f, 0.00999973f, 0.34334624f, 0.21986631f,
  0.79763883f, 0.03195622f, 0.87999827f, 0.93487221f, 0.90384197f, 0.78209203f, 0.66271979f, 0.51759398f, 0.27020827f,
  0.01646276f, 0.25236669f, 0.29880023f, 0.85489792f, 0.54071951f, 0.52771467f, 0.85988355f, 0.80216110f, 0.18511431f,
  0.57248855f, 0.08354635f, 0.73314255f, 0.04427230f, 0.51901162f, 0.44380799f, 0.77088392f, 0.01931875f, 0.56885797f,
  0.06703205f, 0.46570987f, 0.81177151f, 0.34268892f, 0.63629061f, 0.06820934f, 0.77285045f, 0.37792417f, 0.70568216f,
  0.07962608f, 0.23821092f, 0.98281711f, 0.04441794f, 0.18161285f, 0.28121689f, 0.81185871f, 0.86508965f, 0.87496167f,
  0.07312331f, 0.68841326f, 0.66033190f, 0.56949443f, 0.18737859f, 0.16097143f, 0.52228659f, 0.46688002f, 0.90387928f,
  0.34517205f, 0.47515273f, 0.22503996f, 0.84702229f, 0.59251189f, 0.83877939f, 0.31226984f, 0.13928005f, 0.91630554f,
  0.54030454f, 0.90963554f, 0.46708530f, 0.25711828f, 0.21868290f, 0.11089130f, 0.44082832f, 0.19296274f, 0.48027819f,
  0.49958417f, 0.33328432f, 0.72858566f, 0.00891268f, 0.20819443f, 0.50546396f, 0.24803355f, 0.67314726f, 0.85167187f,
  0.05545932f, 0.41584873f, 0.15757963f, 0.61668509f, 0.60510325f, 0.23366614f, 0.31922379f, 0.10196726f, 0.89051712f,
  0.51585704f, 0.79037350f, 0.47714099f, 0.21749923f, 0.15267165f, 0.20020899f, 0.62180620f, 0.68044007f, 0.54401010f,
  0.15621683f, 0.65413737f, 0.51036102f, 0.14454554f, 0.98806471f, 0.75152785f, 0.14469190f, 0.22204915f, 0.04830001f,
  0.51935184f, 0.89906400f, 0.78529602f, 0.71532959f, 0.02233043f, 0.31032783f, 0.32436246f, 0.39294025f, 0.87292236f,
  0.08078373f, 0.84470963f, 0.35212132f, 0.53844059f, 0.00101328f, 0.86660826f, 0.62463045f, 0.94980597f, 0.20027141f,
  0.82640702f, 0.62511158f, 0.85411543f, 0.32145184f, 0.09874340f, 0.04731823f, 0.65130430f, 0.72336477f, 0.70351696f,
  0.75925201f, 0.61024082f, 0.40630430f, 0.79961526f, 0.70433503f, 0.03457122f, 0.58535922f, 0.77023876f, 0.96956450f,
  0.73172861f, 0.30387843f, 0.25969839f, 0.31375539f, 0.25706929f, 0.22646162f, 0.63230330f, 0.67233455f, 0.34529746f,
  0.77892226f, 0.79658866f, 0.51266170f, 0.44614622f, 0.61526495f, 0.78274941f, 0.04566117f, 0.99047178f, 0.44609952f,
  0.30024832f, 0.96801263f, 0.14300583f, 0.35956031f, 0.90130842f, 0.55403215f, 0.54155940f, 0.41135442f, 0.97474039f,
  0.96604657f, 0.63660443f, 0.20305784f, 0.99391299f, 0.99282658f, 0.54607081f, 0.65919995f, 0.52642596f, 0.80907726f,
  0.13542791f, 0.45815086f, 0.35570517f, 0.88730806f, 0.02621857f, 0.53393435f, 0.16039518f, 0.57727945f, 0.74563718f,
  0.91749829f, 0.03039969f, 0.31414652f, 0.36654308f, 0.72613841f, 0.86234623f, 0.80523586f, 0.69267774f, 0.48006293f,
  0.69094217f, 0.48757437f, 0.18863679f, 0.84141004f, 0.44190428f, 0.55552751f, 0.58157742f, 0.26988128f, 0.98975170f,
  0.48674271f, 0.20390622f, 0.27584589f, 0.24773291f, 0.22539048f, 0.26217309f, 0.64675391f, 0.75017244f, 0.92113358f,
  0.45697534f, 0.20047475f, 0.05692944f, 0.87985313f, 0.50851625f, 0.46580771f, 0.21196017f, 0.72498012f, 0.79860425f,
  0.30287132f, 0.29733139f, 0.48900729f, 0.02760601f, 0.20367433f, 0.59343243f, 0.08861626f, 0.84384042f, 0.16568965f,
  0.38101614f, 0.50299650f, 0.74985832f, 0.78758103f, 0.51114148f, 0.90360188f, 0.54095179f, 0.21952409f, 0.95943433f,
  0.73813099f, 0.80396092f, 0.25780290f, 0.03232307f, 0.56420875f, 0.70938724f, 0.13242963f, 0.46500149f, 0.37208769f,
  0.94754893f, 0.08285546f, 0.22143273f, 0.50572622f, 0.26707202f, 0.69440687f, 0.08147397f, 0.45697790f, 0.42861882f,
  0.36127472f, 0.10901877f, 0.81600749f, 0.63378674f, 0.04581152f, 0.80296326f, 0.38782778f, 0.69680047f, 0.45852318f,
  0.76621139f, 0.73573214f, 0.34245411f, 0.90963697f, 0.84585148f, 0.27740547f, 0.42876878f, 0.81776839f, 0.82400990f,
  0.65631586f, 0.62649614f, 0.01128032f, 0.14342305f, 0.73535371f, 0.07838690f, 0.60349464f, 0.01833264f, 0.68001914f,
  0.06672499f, 0.58395982f, 0.45858380f, 0.57352096f, 0.11334193f, 0.36101747f, 0.02778334f, 0.95869988f, 0.75486147f,
  0.98694283f, 0.39485049f, 0.38713542f, 0.74693847f, 0.83618003f, 0.45240483f, 0.98214239f, 0.45008674f, 0.58535296f,
  0.47807249f, 0.67093199f, 0.47400394f, 0.08625654f, 0.80316335f, 0.99145055f, 0.40239251f, 0.77950019f, 0.90468615f,
  0.99436480f, 0.03706104f, 0.65368974f, 0.77387434f, 0.03742794f, 0.12564138f, 0.71908939f, 0.61851358f, 0.68811607f,
  0.01036426f, 0.60881311f, 0.53862727f, 0.10621128f, 0.00301796f, 0.28068480f, 0.95119381f, 0.77621460f, 0.90540200f,
  0.89016628f, 0.79596692f, 0.51059932f, 0.91527432f, 0.71570796f, 0.14555824f, 0.07777888f, 0.15773007f, 0.61530423f,
  0.18763167f, 0.83780384f, 0.62249589f, 0.69600540f, 0.90580952f, 0.55505937f, 0.98995519f, 0.86118966f, 0.71112245f,
  0.74532151f, 0.73180044f, 0.26454931f, 0.90929317f, 0.99976909f, 0.40087372f, 0.57373190f, 0.24985068f, 0.63905895f,
  0.17343017f, 0.48969960f, 0.11945705f, 0.88937473f, 0.81261057f, 0.87451029f, 0.14679237f, 0.84779000f, 0.26429749f,
  0.64772385f, 0.81908917f, 0.58557868f, 0.31058726f, 0.28158280f, 0.98241746f, 0.99165398f, 0.26663870f, 0.79966122f,
  0.53365332f, 0.50163621f, 0.31446701f, 0.77231532f, 0.91077286f, 0.12428004f, 0.36655664f, 0.92101789f, 0.43359232f,
  0.04483659f, 0.51229268f, 0.22860481f, 0.93888646f, 0.84248632f, 0.03094900f, 0.30557162f, 0.71687865f, 0.48432156f,
  0.89101893f, 0.65005356f, 0.02728722f, 0.14394285f, 0.52205127f, 0.30579823f, 0.32598981f, 0.88692045f, 0.85948932f,
  0.88684195f, 0.55851656f, 0.51521665f, 0.69022787f, 0.26708755f, 0.45285350f, 0.88034350f, 0.62830901f, 0.49798331f,
  0.29009685f, 0.33343926f, 0.00934858f, 0.89469659f, 0.57675594f, 0.20448305f, 0.31144422f, 0.81960464f, 0.51726758f,
  0.83883786f, 0.91640586f, 0.52279603f, 0.42647478f, 0.16193789f, 0.24739604f, 0.94897699f, 0.37129375f, 0.05944908f,
  0.93186110f, 0.88649946f, 0.93686837f, 0.57434422f, 0.84432995f, 0.37884688f, 0.92020649f, 0.64090526f, 0.22790030f,
  0.12780701f, 0.08748221f, 0.40670288f, 0.22730973f, 0.35641009f, 0.31437662f, 0.15115604f, 0.17476587f, 0.85647309f,
  0.60709417f, 0.10200764f, 0.41358641f, 0.95312101f, 0.81635153f, 0.16681382f, 0.18513040f, 0.43940443f, 0.70187652f,
  0.16041639f, 0.24035563f, 0.87927175f, 0.57421911f, 0.47845036f, 0.34898761f, 0.39915341f,
};

}  // namespace
