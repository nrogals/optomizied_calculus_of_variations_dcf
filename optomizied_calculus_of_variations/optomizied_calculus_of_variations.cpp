/*
Optomizied Calculus Of Variations.



TODO: Finish by EOD 5-23-2024


1. Finish integral
2. Look at the derivative 
3. Make it only a few flops upon update to a cash flow, via the derivatives.



*/

#include <vector>
#include <cmath>
#include <array>
#include <tuple>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <assert.h>

using namespace std;

const double EPSILON = 0.01;


std::unordered_map<int, int> permutation_map =
{
    {0,20},
    {1,2},
    {2,1},
    {3,4},
    {4,3},
    {5,6},
    {6,5},
    {7,8},
    {8,7},
    {9,10},
    {10,9},
    {11,12},
    {12,11},
    {13,14},
    {14,13},
    {15, 16},
    {16,15},
    {17,17},
    {18,19},
    {19,0},
    {20,18},
    {21,21}
};

constexpr std::array <std::array<double, 22>, 22> lower_part_decomposition = {
                                                                               {
                                                                                    {1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {1.052631578947368363e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {5.263157894736841813e-02,8.725490196078431460e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {2.105263157894736725e-01,8.823529411764703401e-01,-2.821316614420065760e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {1.578947368421052544e-01,9.411764705882352811e-01,-3.009404388714735923e-01,8.303703703703700922e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {3.157894736842105088e-01,7.647058823529411242e-01,-2.445141065830725435e-01,8.666666666666659191e-01,-2.985455473335042464e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {2.631578947368420907e-01,8.235294117647055101e-01,-2.633228840125412806e-01,9.333333333333317938e-01,-3.215105894360831829e-01,8.365231259968106681e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {4.210526315789473450e-01,6.470588235294113533e-01,-2.068965517241380669e-01,7.333333333333335036e-01,-2.526154631283495378e-01,8.461538461538452571e-01,-2.922271889498548880e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {3.684210526315789269e-01,7.058823529411757391e-01,-2.257053291536068040e-01,7.999999999999997113e-01,-2.755805052309271419e-01,9.230769230769235723e-01,-3.187932970362024609e-01,8.452213651457897159e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {5.263157894736841813e-01,5.294117647058815823e-01,-1.692789968652070043e-01,5.999999999999982014e-01,-2.066853789231978544e-01,6.923076923076922906e-01,-2.390949727771538025e-01,8.181818181818186764e-01,-2.834188249930105763e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {4.736842105263157632e-01,5.882352941176459682e-01,-1.880877742946740483e-01,6.666666666666657415e-01,-2.296504210257731271e-01,7.692307692307686073e-01,-2.656610808635059828e-01,9.090909090909088386e-01,-3.149098055477916325e-01,8.577871866193487183e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {6.315789473684210176e-01,4.117647058823527551e-01,-1.316614420062697799e-01,4.666666666666659524e-01,-1.607552947180411196e-01,5.384615384615382139e-01,-1.859627566044524671e-01,6.363636363636372417e-01,-2.204368638834523775e-01,7.777777777777787893e-01,-2.706007104085026427e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {5.789473684210526550e-01,4.705882352941191393e-01,-1.504702194357338263e-01,5.333333333333327708e-01,-1.837203368206175302e-01,6.153846153846145306e-01,-2.125288646908071732e-01,7.272727272727261827e-01,-2.519278444382352933e-01,8.888888888888882844e-01,-3.092579547525778905e-01,8.775334871561482064e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {7.368421052631578538e-01,2.941176470588219849e-01,-9.404388714733839805e-02,3.333333333333333703e-01,-1.148252105128864525e-01,3.846153846153851363e-01,-1.328305404317483840e-01,4.545454545454553075e-01,-1.574549027738948725e-01,5.555555555555566905e-01,-1.932862217203576982e-01,7.142857142857154118e-01,-2.502299457696772200e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {6.842105263157893802e-01,3.529411764705863708e-01,-1.128526645768055253e-01,3.999999999999995226e-01,-1.377902526154637930e-01,4.615384615384616751e-01,-1.593966485181023962e-01,5.454545454545451921e-01,-1.889458833286753459e-01,6.666666666666674068e-01,-2.319434660644292268e-01,8.571428571428587606e-01,-3.002759349236127639e-01,9.130768281804442221e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {8.421052631578946901e-01,1.764705882352931854e-01,-5.642633228840106263e-02,2.000000000000012601e-01,-6.889512630773131363e-02,2.307692307692294775e-01,-7.969832425905119810e-02,2.727272727272742059e-01,-9.447294166433527207e-02,3.333333333333339255e-01,-1.159717330322140305e-01,4.285714285714293248e-01,-1.501379674618070759e-01,5.999999999999999778e-01,-2.128433977706177538e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {7.894736842105263275e-01,2.352941176470595697e-01,-7.523510971786520618e-02,2.666666666666678842e-01,-9.186016841030819613e-02,3.076923076923059885e-01,-1.062644323454053075e-01,3.636363636363617036e-01,-1.259639222191215879e-01,4.444444444444440867e-01,-1.546289773762880015e-01,5.714285714285728401e-01,-2.001839566157405104e-01,8.000000000000019318e-01,-2.837911970274880624e-01,9.960112905708602415e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {8.947368421052630527e-01,1.176470588235287856e-01,-3.761755485893403944e-02,1.333333333333325266e-01,-4.593008420515427154e-02,1.538461538461555755e-01,-5.313221617269690139e-02,1.818181818181838771e-01,-6.298196110955321669e-02,2.222222222222229315e-01,-7.731448868814261299e-02,2.857142857142864201e-01,-1.000919783078701303e-01,4.000000000000012990e-01,-1.418955985137427267e-01,6.666666666666666297e-01,-2.436611980656384902e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {5.263157894736841813e-02,-5.882352941176476752e-02,1.880877742946712727e-02,-6.666666666666652696e-02,2.296504210257730924e-02,-7.692307692307699674e-02,2.656610808635037971e-02,-9.090909090909086998e-02,3.149098055477900920e-02,-1.111111111111113964e-01,3.865724434407147997e-02,-1.428571428571430435e-01,5.004598915393535657e-02,-2.000000000000005940e-01,7.094779925687165478e-02,-3.333333333333330373e-01,1.218305990328197308e-01,-7.088761776287281213e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {9.473684210526315264e-01,5.882352941176240829e-02,-1.880877742947319534e-02,6.666666666666551389e-02,-2.296504210257836742e-02,7.692307692307639999e-02,-2.656610808635417528e-02,9.090909090908998180e-02,-3.149098055477975860e-02,1.111111111111112021e-01,-3.865724434407153548e-02,1.428571428571433211e-01,-5.004598915393495412e-02,2.000000000000003164e-01,-7.094779925687241806e-02,3.333333333333328707e-01,-1.218305990328202165e-01,7.088761776287284544e-01,-6.220084679281455697e-01,1.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {8.771929824561403022e-03,1.764705882352941013e-01,2.633228840125390602e-01,1.185185185185180443e-02,1.888236795100785986e-02,8.587903324745153758e-04,1.355846026735518491e-03,6.245901127380908168e-05,9.736132771992086728e-05,4.567398820679700792e-06,6.991896868186618294e-06,3.372937522213932660e-07,5.021859340992940128e-07,2.542743193823600064e-08,3.608040672275432095e-08,2.028452750988727340e-09,2.594839955189548036e-09,1.548572251492858763e-10,2.926735989328732325e-11,-4.971733642394500891e-11,1.000000000000000000e+00,0.000000000000000000e+00},
                                                                                    {0.000000000000000000e+00,-0.000000000000000000e+00,0.000000000000000000e+00,-0.000000000000000000e+00,0.000000000000000000e+00,-0.000000000000000000e+00,0.000000000000000000e+00,-0.000000000000000000e+00,0.000000000000000000e+00,-0.000000000000000000e+00,0.000000000000000000e+00,-0.000000000000000000e+00,0.000000000000000000e+00,-0.000000000000000000e+00,0.000000000000000000e+00,-0.000000000000000000e+00,0.000000000000000000e+00,-0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,1.000000000000000000e+00}
                                                                                }
                                                                            };
 
constexpr std::array <std::array<double, 22>, 22> upper_part_decomposition = {
                                                                               {
                                                                                    {1.900000000000000000e+01,1.800000000000000000e+01,1.700000000000000000e+01,1.600000000000000000e+01,1.500000000000000000e+01,1.400000000000000000e+01,1.300000000000000000e+01,1.200000000000000000e+01,1.100000000000000000e+01,1.000000000000000000e+01,9.000000000000000000e+00,8.000000000000000000e+00,7.000000000000000000e+00,6.000000000000000000e+00,5.000000000000000000e+00,4.000000000000000000e+00,3.000000000000000000e+00,2.000000000000000000e+00,1.000000000000000000e+00,1.666666666666666574e-01,1.000000000000000000e+00,1.950000000000000000e+01},
                                                                                    {0.000000000000000000e+00,-8.947368421052630527e-01,-1.622807017543859365e+00,-1.684210526315789380e+00,-1.578947368421052655e+00,-1.473684210526315708e+00,-1.368421052631578760e+00,-1.263157894736842035e+00,-1.157894736842105310e+00,-1.052631578947368363e+00,-9.473684210526315264e-01,-8.421052631578946901e-01,-7.368421052631578538e-01,-6.315789473684210176e-01,-5.263157894736841813e-01,-4.210526315789473450e-01,-3.157894736842105088e-01,-2.105263157894736725e-01,-1.052631578947368363e-01,-1.754385964912280604e-02,8.947368421052631637e-01,4.473684210526318594e-01},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,5.212418300653594017e-01,6.274509803921568540e-01,5.882352941176471894e-01,5.490196078431371918e-01,5.098039215686274161e-01,4.705882352941175295e-01,4.313725490196078649e-01,3.921568627450979783e-01,3.529411764705882582e-01,3.137254901960784270e-01,2.745098039215685959e-01,2.352941176470587648e-01,1.960784313725489891e-01,1.568627450980392135e-01,1.176470588235293824e-01,7.843137254901960675e-02,3.921568627450980338e-02,6.535947712418299985e-03,1.666666666666667407e-01,8.333333333333320381e-02},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,-7.053291536050159127e-01,-1.432079414838035580e+00,-1.492163009404388951e+00,-1.385579937304075138e+00,-1.278996865203761990e+00,-1.172413793103448398e+00,-1.065830721003135029e+00,-9.592476489028214370e-01,-8.526645768025079564e-01,-7.460815047021944757e-01,-6.394984326018809950e-01,-5.329153605015675144e-01,-4.263322884012539782e-01,-3.197492163009404975e-01,-2.131661442006269891e-01,-1.065830721003134945e-01,-1.776384535005224793e-02,4.702194357366800553e-02,2.351097178683428726e-02},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,4.838271604938271242e-01,5.807407407407405575e-01,5.392592592592589940e-01,4.977777777777778745e-01,4.562962962962964220e-01,4.148148148148147474e-01,3.733333333333332948e-01,3.318518518518518423e-01,2.903703703703701677e-01,2.488888888888889372e-01,2.074074074074073737e-01,1.659259259259259212e-01,1.244444444444444686e-01,8.296296296296296058e-02,4.148148148148148029e-02,6.913580246913575422e-03,1.111111111111096061e-02,5.555555555554869684e-03},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,-6.932891043633579997e-01,-1.405673215956452005e+00,-1.451390660882878159e+00,-1.330441439142638460e+00,-1.209492217402398762e+00,-1.088542995662159063e+00,-9.675937739219188094e-01,-8.466445521816791109e-01,-7.256953304414391903e-01,-6.047461087011993808e-01,-4.837968869609594047e-01,-3.628476652207195952e-01,-2.418984434804797023e-01,-1.209492217402398512e-01,-2.015820362337331431e-02,3.317172748150002196e-03,1.658586374074208112e-03},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,4.825890483785225671e-01,5.741626794258378741e-01,5.263157894736854026e-01,4.784688995215322649e-01,4.306220095693791272e-01,3.827751196172253234e-01,3.349282296650721857e-01,2.870813397129190481e-01,2.392344497607661324e-01,1.913875598086126617e-01,1.435406698564595240e-01,9.569377990430633085e-02,4.784688995215316543e-02,7.974481658692196551e-03,7.974481658697962771e-04,3.987240829354532501e-04},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,-6.783679003453171319e-01,-1.371837241983207667e+00,-1.398639916954431239e+00,-1.258775925258987849e+00,-1.118911933563545347e+00,-9.790479418681016233e-01,-8.391839501726591211e-01,-6.993199584772156197e-01,-5.594559667817726734e-01,-4.195919750863295605e-01,-2.797279833908863367e-01,-1.398639916954431683e-01,-2.331066528257386486e-02,2.330360358455702149e-04,1.165180179241130654e-04},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,4.811382460815645246e-01,5.654622487326028679e-01,5.089160238593428698e-01,4.523697989860823165e-01,3.958235741128215412e-01,3.392773492395620427e-01,2.827311243663014340e-01,2.261848994930411583e-01,1.696386746197810214e-01,1.130924497465205791e-01,5.654622487326028957e-02,9.424370812210054044e-03,5.725409366830511810e-05,2.862704683339598922e-05},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,-6.579191720681163424e-01,-1.325460588194638190e+00,-1.326335337654493962e+00,-1.160543420447681662e+00,-9.947515032408698055e-01,-8.289595860340578382e-01,-6.631676688272469811e-01,-4.973757516204349027e-01,-3.315838344136234905e-01,-1.657919172068117453e-01,-2.763198620113527584e-02,1.622688795454101153e-05,8.113443977576157605e-06},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,4.790439368541894449e-01,5.528964159621462260e-01,4.837843639668770734e-01,4.146723119716090311e-01,3.455602599763405447e-01,2.764482079810731130e-01,2.073361559858045156e-01,1.382241039905365565e-01,6.911205199526827825e-02,1.151867533254469222e-02,4.110658938991126172e-06,2.055329468405052212e-06},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,-6.281636148361041672e-01,-1.257976496314926029e+00,-1.221122711127079041e+00,-1.017602259272566645e+00,-8.140818074180524722e-01,-6.105613555635397427e-01,-4.070409037090262361e-01,-2.035204518545131180e-01,-3.392007530908551505e-02,1.112347228359306858e-06,5.561736126628635892e-07},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,4.757528867356051183e-01,5.331501153671103221e-01,4.442917628059259716e-01,3.554334102447409549e-01,2.665750576835554941e-01,1.777167051223704219e-01,8.885835256118521097e-02,1.480972542686419258e-02,2.951320308696524079e-07,1.475660140963159416e-07},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,-5.808755898303032961e-01,-1.150729658191919746e+00,-1.053917059886868568e+00,-7.904377949151522031e-01,-5.269585299434341730e-01,-2.634792649717170865e-01,-4.391321082861956299e-02,7.385087380532045894e-08,3.692543682873977666e-08},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,4.698289965647417521e-01,4.976067743425180989e-01,3.732050807568894069e-01,2.488033871712589384e-01,1.244016935856294692e-01,2.073361559760494854e-02,2.118952693778259570e-08,1.059476412453291551e-08},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,-4.940876833952619340e-01,-9.538990958797786135e-01,-7.470438416976310503e-01,-3.735219208488155251e-01,-6.225365347480250888e-02,4.510050546190178072e-09,2.255027528299870227e-09},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,4.560065861663348263e-01,4.146723119520968615e-01,2.073361559760484307e-01,3.455602599600802322e-02,1.521337130678186645e-09,7.606658273713472491e-10},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,-3.989604476651039122e-01,-2.828135571658854097e-01,-4.713559286098090856e-02,3.706909676905032698e-10,1.853447816459993562e-10},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,4.409269851976060917e-01,9.068211641996009043e-01,7.742888892842213208e-11,3.871515837518907284e-11},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,4.905626121623433700e-01,-2.926422332144815610e-11,-1.463152111727614013e-11},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,7.886751345948128655e-01,2.276709006307398864e-01},
                                                                                    {0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,1.000000000000000000e+00}
                                                                                 }
                                                                                };


auto calculate_lambdas_and_initial_conditions(vector<double> cash_flows) {


    //Need to do on full vector. 
    //Apply P^-1 operator
    //permutation_decomposition
    vector<double> lhs = cash_flows;
    lhs.emplace_back(0);
    lhs.emplace_back(0);
    int n = lhs.size();
    vector<double> permuted_lhs(n, 0.0);
    for (int i = 0; i < n; i++) {
        int new_position = permutation_map[i];
        permuted_lhs[new_position] = lhs.at(i);
    }
    
    //permuted_lhs is correct. 
    //Apply L^-1 operator
    vector<double> y = permuted_lhs;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            y[i] = y[i] - lower_part_decomposition[i][j] * y[j];
        }
        double divisor = lower_part_decomposition[i][i];
        if (abs(divisor) < EPSILON) {
            throw exception("Cannot divide by small number");
        }
         
        y[i] = y[i] / divisor;
    }
    
    //Apply U^-1 operator
    for (int i = 0; i < n; i++) {
        int i_index = n - 1 - i;
        for (int j = 0; j < i; j++) {
            int j_index = n - 1 - j;
            y[i_index] = y[i_index] - upper_part_decomposition[i_index][j_index] * y[j_index];
        }
        double divisor = upper_part_decomposition[i_index][i_index];

        if (abs(divisor) < EPSILON) {
            throw exception("Cannot divide by small number");
        }

        y[i_index] = y[i_index] / divisor;
    }

    vector<double> lambdas(n - 2, 0.0);
    for (int i = 0; i < n - 2; i++) {
        lambdas[i] = y[i];
    }
    
    double c_0 = y[n - 2];
    double c_0_prime = y[n - 1];

    
    auto result = std::make_tuple(lambdas, c_0, c_0_prime);
    return result;
}
   


inline double calculate_c_t_via_parameters(double t, vector<double> lambdas) {

    double val = 0.0;
    for (int i = 1; i < int(floor(t)); i++) {
        for (int j = 1; j < i + 1; j++) {
            val += lambdas[j - 1];
        }
        val += lambdas[i] / 2.0;
    }
    
    val += std::min(pow(t, 2.0), 1.0) * lambdas[0] / 2.0;

    int intermediate_val = 0;
    if (t >= 1) {
        for (int i = 1; i < floor(t) + 1; i++) {
            intermediate_val += lambdas[i - 1];
        }
        intermediate_val += 0.5 * lambdas[ceil(t) - 1] * (t - floor(t));
        intermediate_val = intermediate_val * (t - floor(t));
    }
    else {
        intermediate_val = 0.0;
    }

    val += intermediate_val;

    return val;
}


auto calculate_parameterizied_cash_flow(double t, vector<double>& lambdas, double c_0, double c_0_prime) {
    return calculate_c_t_via_parameters(t, lambdas) + c_0_prime * t + c_0;
};



// TODO: Consider if more testing is appropiate. 
// Add the integral 
bool run_tests() {


    vector<double> cash_flows = { 0, 0, 0, 0, 100, 0, 0, 0, 0, 100, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0 };
    auto parameters = calculate_lambdas_and_initial_conditions(cash_flows);
    vector<double> lambdas = std::get<0>(parameters);
    double c_0 = std::get<1>(parameters);
    double c_0_prime = std::get<2>(parameters);
    auto c_t_at_ten = calculate_parameterizied_cash_flow(10.0, lambdas, c_0, c_0_prime);
    double c_t_at_nineteen = calculate_parameterizied_cash_flow(19.0, lambdas, c_0, c_0_prime);
    double true_c_t_at_nineteen = 0.349;
    double true_c_t_at_ten = 63.63;
    bool nineteen_values_close = (abs(c_t_at_nineteen - true_c_t_at_nineteen) < EPSILON);
    bool ten_values_close = (abs(c_t_at_ten - true_c_t_at_ten) < EPSILON);
    return nineteen_values_close and ten_values_close;

}




int main() {

    cout << "Running Tests ... \n";
    bool tests_run_sucessfully = run_tests();
    assert(tests_run_sucessfully);
    cout << "Tests Run Sucessfully ... \n";


    int n = 1000000;
    for (int i = 0; i < n; i++) {
        vector<double> cash_flows = { 0, 0, 0, 0, 100, 0, 0, 0, 0, 100, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0 };
        auto parameters = calculate_lambdas_and_initial_conditions(cash_flows);

    }
}


