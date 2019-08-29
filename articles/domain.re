= ドメイン名とWhois

自分のドメイン名を買ったことはありますか？まだ買ったことがないなら、ドメイン名を買うのはあなたが想像しているよりずっと簡単です。なんといってもDNSのDはドメインのDですし、DNSを理解するにはドメイン名を買って手を動かしてあれこれ試してみるのがいちばんです。という訳でまずは自分のドメイン名を買ってみましょう。

//pagebreak

== ドメイン名のお店選び

それではまずどこでドメイン名を買う@<fn>{buyDomain}のか、お店を決めましょう。

//footnote[buyDomain][ところでドメイン名って「買う」ものなの？という疑問については後述しますので取りあえず進みましょう]

お手元のパソコンでブラウザを開いて「ドメイン」で検索（@<img>{searchDomain}）してみてください。検索結果にはお名前.com、名づけてねっと、Yahoo!ドメイン、ムームードメイン、VALUE DOMAIN、ゴンベエドメインなど、たくさんのお店が出てきます。

//image[searchDomain][ドメインで検索][scale=0.8]{

//}

どこも「ドメイン取得なら〇〇」「ドメイン取るなら△△」のように書いてありますが、一体どのお店で買うのがいいのでしょう？今回は勉強用ですし出来れば安く買いたいですが、そもそもお店によって値段にどれくらい違いがあるのでしょう？取りあえず1軒ずつ見ていってみましょう。

ここでは仮に「筆者が株式会社イグザンプルという会社の広報担当になったのでexample.co.jpというドメイン名を買おうとしている」という設定であちこちのお店を見てみます。

=== お名前.com

お名前.com@<fn>{onamaeURL}でexample.co.jpを調べてみると、1年で3,660円@<fn>{money}でした。（@<img>{onamae3660yen}）しかも残念ながら×がついて「登録済みドメインのため、お申込みいただけません。」となっています。@<fn>{cannotbuy}

//image[onamae3660yen][お名前.comでは3,660円][scale=0.8]{

//}

//footnote[onamaeURL][@<href>{https://www.onamae.com/}]
//footnote[money][ドメイン名の値段はすべて税別（ゴンベエドメインのみ税込）表記で、2019年8月に著者が検索した時点の金額です。]
//footnote[cannotbuy][正確には売り切れというよりも、example.co.jpは例示用のドメイン名なので購入ができません。詳細は@<chapref>{dig}で後述します。]

=== 名づけてねっと

続いてNTTPCコミュニケーションズの名づけてねっと@<fn>{naduketeURL}で、example.co.jpの値段を見てみましょう。example.co.jpは属性JP1年プランというプラン名で7,200円でした。（@<img>{nadukete7200yen}）

//image[nadukete7200yen][名づけてねっとでは7,200円][scale=0.8]{

//}

//footnote[naduketeURL][@<href>{https://www.nadukete.net/}]

=== Yahoo!ドメイン

Yahoo!ドメイン@<fn>{domainsYahooURL}でもexample.co.jpの値段を調べてみましょう。おや？どうしたのでしょう？プルダウンにco.jpがありません。（@<img>{yahooDomain}）

//image[yahooDomain][プルダウンにco.jpがない][scale=0.8]{

//}

//footnote[domainsYahooURL][@<href>{https://domains.yahoo.co.jp/}]

「取得できるドメインの種類」（@<img>{doNotSellCoJp}）を確認したところ、Yahoo!ドメインではどうやら〇〇.co.jpというドメイン名は取り扱いがないためexample.co.jpは買えないようです。

//image[doNotSellCoJp][Yahoo!ドメインではco.jpの取り扱いなし][scale=0.8]{

//}

=== ムームードメイン

ムームードメイン@<fn>{muumuuURL}はお名前.comより少し高い3,980円でした。（@<img>{muumuu3980yen}）

//image[muumuu3980yen][ムームードメインでは3,980円][scale=0.8]{

//}

//footnote[muumuuURL][@<href>{https://muumuu-domain.com/}]


=== VALUE DOMAIN

VALUE DOMAIN@<fn>{valueDomainURL}は3,780円でした。（@<img>{valueDomain3780yen}）

//image[valueDomain3780yen][VALUE DOMAINでは3,780円][scale=0.8]{

//}

//footnote[valueDomainURL][@<href>{https://www.value-domain.com/}]

=== ゴンベエドメイン

品揃え日本一！と謳っているゴンベエドメイン@<fn>{gonbeiURL}はどうでしょう？こちらは少し高めの5,616円でした。（@<img>{gonbei5616yen}）

//image[gonbei5616yen][ゴンベエドメインでは5,616円][scale=0.6]{

//}

//footnote[gonbeiURL][@<href>{https://www.gonbei.jp/}]

金額だけで比べるとお名前.comで買うのがよさそうです。（@<table>{domainFee}）

//table[domainFee][example.co.jpのドメイン名代]{
お店	金額
------------------------------------
名づけてねっと	7,200円
ゴンベエドメイン	5,616円
ムームードメイン	3,980円
VALUE DOMAIN	3,780円
お名前.com	3,660円
Yahoo!ドメイン	取り扱いなし
//}

しかしこうして金額を並べてみると色々な疑問が湧いてきませんか？一番高い名づけてねっとの7,200円は、一番安いお名前.comの3,660円と比較すると倍近い金額です。なぜこんなに金額に差があるのでしょう？それになぜYahoo!ドメインだけexample.co.jpを取り扱っていなかったのでしょう？

== 値段やお店によってドメイン名の品質は違うのか

あまりに金額に差があるので、もしかして同じ「ドメイン名」いう名前がついていてもどのお店で買ったのかや、その金額によって何か違いがあるのだろうか？と株式会社イグザンプルに勤める筆者はちょっと不安になってきました。あなたはAとBのどちらだと思いますか？答えを書きこんでみましょう。

 * A. 同じドメイン名でも買うお店や金額によって何かしら品質に違いがある
 * B. 品質に違いはなく、どこで買ってもドメイン名はドメイン名である

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

正解はBです。ドメイン名はどこのお店で買っても品質に差はありません。プロ向けに業務用のドメイン名屋さんがあるわけではないので、Web制作会社でもよくお名前.comでドメイン名を購入しています。ロボット掃除機のルンバはどこで買っても同じルンバですが、ヤマダ電機とヨドバシカメラで値段は異なりますよね。ルンバと同じようにドメイン名もどこで買っても同じドメイン名ですがお店によって値段が違うのです。

「なるほど！どこで買ってもドメイン名はドメイン名。なら深く考えずに安いお店で買おう！」と思われた方、ちょっと待ってください。ドメイン名の品質に差はなくても、どこで買うかはよく考えた方がいいんです。なぜならドメイン名を売るお店には大きく分けて2つの種類があるからです。

== ドメイン名を売るお店はレジストラとリセラの2種類

ここまで「ドメイン名のお店」とひとくくりに呼んでいましたが、実はお名前.comやゴンベエドメインは「レジストラ（登録事業者）」です。そして名づけてねっとやYahoo!ドメイン、ムームードメイン@<fn>{muumuu}、VALUE DOMAINはレジストラの下にいる「リセラ（再販事業者）」です。（@<img>{registrarAndReseller}）

//footnote[muumuu][正確にはムームードメインはjpドメインにおいてのみレジストラです。それ以外のTLDはレジストラ（eNomとお名前.com）から仕入れてリセラとして販売しています。]

//image[registrarAndReseller][レジストラとリセラ][scale=0.8]{
//}

レジストラ？リセラ？いきなり知らない単語が出てきましたね。一体何なのでしょう？

「リセラ（再販事業者）はレジストラ（登録事業者）からドメイン名を仕入れて、それを再販している」という表現だと分かりやすいでしょうか。つまりムームードメインは、お名前.comなどのレジストラからドメイン名を仕入れてそれを再販している再販事業者なのです。

ドメイン名を買うときに、そのお店がレジストラなのかリセラなのか意識して買う人はほとんどいないと思います。お店にレジストラとリセラという種類があることなんて知らなかった、という人の方が多いのではないでしょうか。

レジストラとリセラのどちらから買ったとしても、ルンバと同じでドメイン名としての品質には変わりありません。しかし中間業者が増えるほど、そのお店が倒産してしまい連絡が取れなくなるといったリスクも増えるので、どちらかといえばレジストラから買った方がそのリスクは軽減されます。
またお店を選ぶときに見るべきポイントは、レジストラかリセラかだけでなく、他にもいくつかあります。

=== お店選びのポイント

お店によっては「初年度は99円だけど2年目からは7,980円」のように、最初のキャンペーン価格が安いだけで2年目以降の標準価格が高い場合があります。長く使うと思われるドメイン名の場合は2年目以降の更新にかかる金額も確認しましょう。

それから、ドメイン名を買うとそのドメイン名に関する設定変更は無料で、管理画面上でボタンをぽちっと押せばすぐに反映される、というお店もあれば、何か変更するたびにメールでの依頼が必要で、都度変更手数料がかかって設定完了までは最低3営業日を要する、というお店もあります。ドメイン名の金額が同じなら前者の方がいいですよね。

さらにお店によってはドメイン名を買うとサーバが数か月分無料でついてくる、といった無料オプションがあったりします。

前述のようにドメイン名の品質はどこのお店で買っても同じですので、2年目以降の金額や管理画面の使いやすさ、無料オプションの充実度などを見てどこで買うかを考えるのがいいでしょう。

迷ったら取りあえずお名前.comを使っておけば間違いはありません。何しろ取り扱うドメイン名は550種類以上で、累積登録実績1600万件という国内最大のレジストラです。国内だけでなく世界中のレジストラを対象にした新gTLD@<fn>{gTld}の保有数ランキング（@<img>{ntldStats}）でもトップ5に入るほどの規模なのです。

//footnote[gTld][generic Top Level Domainの略。gTLDの一覧は@<href>{https://www.nic.ad.jp/ja/dom/types.html}を参照。]

//image[ntldStats][新gTLDの保有数が多いレジストラランキング][scale=0.8]{
//}

===[column] 【コラム】ドメイン界の巨人 GMOインターネット

余談ですがお名前.comもムームードメインもVALUE DOMAINもすべてGMOインターネットグループのサービスですので、この3箇所であればどこで買っても同じといえば同じです。（金額はお名前.comが若干安かったですね）

渋谷でセルリアンタワー@<fn>{cerulean}に描かれたGMOのロゴを見るたび、ここに何かあったら日本のインターネットの何割が止まるんだろう、と思います。

===[/column]

//footnote[cerulean][@<href>{https://www.gmo.jp/company-profile/outline/}]

== ドメイン名が生まれてから手元に届くまで

さて折角、レジストラとリセラの話が出てきたので、ドメイン名が生まれてから私たちの手元にやってくるまでの流れも知っておきましょう。

先ほどリセラ（再販事業者）はレジストラ（登録事業者）からドメイン名を仕入れて売っている、という話をしました。ではレジストラはいったいどこからドメイン名を仕入れているのでしょう？どこかにドメイン名が湧く泉があるのか、それとも種を植えると畑からドメイン名が収穫できるのでしょうか？

=== ドメイン名の卸元はレジストリ

残念ながらドメイン名は畑からは採れません。レジストラはドメイン名をレジストリ（登録管理組織）から仕入れています。

レジストラ？レジストリ？ごちゃごちゃしてきたのでちょっと図で整理してみましょう。ドメイン名は一番上のレジストリからレジストラに卸され、そこからさらにリセラに卸されます。私たちはドメイン名が買いたかったら、前述のとおりレジストラから買うこともリセラから買うこともできます。（@<img>{registrarAndRegistry}）

//image[registrarAndRegistry][レジストラとレジストリ][scale=0.8]{
//}

今回のようにexample.co.jpというドメイン名が欲しい場合は、リセラのYahoo!ドメインからでもレジストラのお名前.comからでも購入できて、実はどちらから買っても卸元は同じということです。

ドメイン名の卸元はレジストリだった、ということを知っていましたか？お名前.comは知っていてもレジストリのことまで知っている人は少ないのではないでしょうか。このように一般にはほぼ認知されていないレジストリですが、実際ドメイン名を買うときは、ドメイン名を買う人＝つまり私たちはレジストリと直接「ドメイン名登録契約」を結んでいます。間に居るレジストラやリセラはその登録契約の仲介をしているにすぎません。

では卸元であるレジストリとはいったいどんな存在なのでしょうか？

=== 1つのTLDには1つのレジストリ

そもそもドメイン名は「example.co.jp」や「yahoo.com」のように.（ドット）で区切られています。このとき、いちばん右側のjpやcomをTLD（トップレベルドメイン）と呼びます。@<fn>{tdl}そしてこのTLDは、1つにつき必ず1つのレジストリ（登録管理組織）によって管理されています。

//footnote[tdl][TDLだと東京ディズニーランドになってしまいます。TLDです。]

たとえばexample.co.jpのTLDはjpですが、このjpというTLDは、日本の「株式会社日本レジストリサービス」（通称JPRS）がレジストリです。JPRSという社名を見聞きしたことはありますか？最近は車内広告を出したりしているのでもしかしたら見たことがあるかもしれません。

それから、yahoo.comなどで使われているcomというTLDのレジストリは「VeriSign Global Registry Services」です。VeriSign Global Registry Servicesはcomだけでなくnetやnameなど複数のTLDを保有しています。

2020年の東京オリンピックに向けて販売に力を入れている.tokyoというTLD（@<img>{tokyo}）は、お名前.comと同じGMOグループに属しているGMOドメインレジストリ株式会社がレジストリです。

//image[tokyo][.tokyoドメイン][scale=0.8]{
//}

また2014年ごろにGoogleが「.みんな」のレジストリになって、「どんな○○.みんなが欲しいですか？」というキャンペーン（@<img>{minna}）をしていました。このようにTLDは英語だけでなく日本語やさまざまな言語で存在しており、それぞれのTLDに必ず1つのレジストリが存在しています。

//image[minna][Googleのはじめよう.みんな][scale=0.8]{
//}

=== ＜トラブル＞Mackerelのアラート誤報はioドメインが原因

2017年9月、株式会社はてなが提供しているサーバ監視サービスのMackerelで、ioドメインの不調によってアラート誤報を出してしまった、というトラブル（@<img>{mackerel}）がありました。これはioドメインのネームサーバが、Mackrelのmackerel.ioというドメイン名について名前解決のリクエストを受けてもきちんと応答できなかったことで、監視対象のサーバがMackerelシステムに通信できなくなり、Mackerelシステムが「監視対象のサーバから連絡が来ない！死んだのか！」と判断して誤発報してしまった、という障害でした。

//image[mackerel][Mackerelの死活監視アラートの誤報を報告するブログ][scale=0.8]{
//}

このトラブルは信用できるレジストリのTLDを選ぶ以外に回避策がありません。絶対に落とせないサイトやメールを消失させたくないメールアドレスなどで、.ioのようにトラブルを起こしたことのあるTLDを採用するのはあまりお勧めしません。ドメイン名を買うときは、このTLDはどこのレジストリが管理しているのだろう？過去に障害は発生していないか？と事前に確認しておきましょう。たとえばjpドメインのJPRSやtokyoドメインのGMOインターネットなら、レジストリとしての実績があるため安心です。

=== 【ドリル】ネットショップのドメイン名は〇〇.xxx？〇〇.com？

==== 問題

あなたはとあるアパレルショップのウェブマーケティング担当です。このたび、担当するブランドでネットショップを作ることになりました。当初はネットショップのドメイン名を〇〇.comにする予定でしたが、ブランド名に「KISS」を含むため「〇〇.xxx」にしたい、という提案がデザインチーム内から上がりました。なお国内外で大規模な宣伝を行うため、上司からは「ネットショップがダウンすることや特定の地域や環境からサイトが閲覧できない状況は何より避けたい」と言われています。ドメイン名はどちらにすべきでしょうか？

 * A. 当初の予定通りドメイン名は〇〇.comにする
 * B. 提案を受け入れてドメイン名は〇〇.xxxにする

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はAです。.xxxはアダルトコンテンツ専用に用意されたTLDで、国によってはTLDごと閲覧をブロックされています。ブランドイメージを損なうとともに、今回のケースではネットショップが閲覧できない状況を避けるのが何より優先ですので〇〇.comにすべきです。

===[column] 【コラム】ブランドTLDとGMOドメインレジストリ

最近は.canonや.toshibaのように企業がブランドTLDをもつことも増えてきました。ブランドTLDは日本ですとGMOドメインレジストリ株式会社@<fn>{gmoDomain}に、TLDの取得やレジストリとしての運用を支援してもらうケースが多いようです。

===[/column]

//footnote[gmoDomain][@<href>{https://www.gmoregistry.com/}]

== なぜレジストリがそのTLDを独占するのか

このようにTLDにはそれぞれ1社ずつレジストリがいて、そのTLDの唯一の卸元となっています。

たとえばexample.jpのようにjpで終わるドメイン名なら、先ほどのJPRSが唯一の卸元です。example.co.jpが欲しいときも、example.ne.jpが欲しいときも、example.jpが欲しいときもすべてJPRSがレジストラに卸して（あるいはさらにレジストラからリセラに卸して）そこで私たちが買うのです。

ちなみに卸元のレジストリから、ドメイン名を直接買うことはできません。必ずレジストラもしくはリセラを通して購入することになります。

それにしてもお名前.comで買おうがムームードメインで買おうが、jpで終わるドメイン名が売れたら必ずJPRSにお金が入るなんて！競争相手もいないし、卸元のJPRSは独占で大儲け！と羨ましく思いますが、実際はレジストリが丸儲けしたいがためにこんな構造になっているわけではありません。

AさんとBさんが同時にexample.co.jpを買ってしまい、二人とも使おうとしてどちらのサイトを表示したらいいのか大混乱！のようなことが起こらないようにするため、つまりドメイン名の一意性を保つためにレジストリがそのTLDを一元管理しています。

前述のioドメインのように、レジストリがそのTLDをきちんと管理してくれないと大変なことになるので、誰でも彼でもレジストリになれる訳ではなく、レジストリになるにはものすごい大金と政府の推薦などが必要なのだそうです。（ブランドTLDはそうした条件が緩和されているため取りやすいようです）

===[column] 【コラム】他のドメイン名と比べてjpドメインが高い理由

レジストリはそのTLDの唯一の卸元ですので、もちろん卸値もレジストリが決められます。新興の.workや.xyzなどは卸値が安いのでお名前.comでも1円～30円という破格ですが、jpは元々の卸値が高いので2,480円と少し高めの価格で売られています。

一度、GMOインターネットの熊谷社長が「.jpは他のccTLD@<fn>{ccTld}に比べて高すぎる、独占企業だからって高い値段で売ってないで値下げしようよ」とJPRSに公開質問@<fn>{kumagai}を投げかけたこともあるほどです。

しかし値段の分だけあって、JPRSは管理体制もしっかりしているので前述のioドメインのような障害が起きるリスクは低いといえます。ひとたび障害が起きれば対応する人件費もかかりますし、jpドメインのドメイン名が少々高くても安心代と思えば安いのかも知れません。

高いといえば1年で250,000円かかる.richというドメイン名もあります。もしあなたがリッチなことをアピールしたければ、「自分の名前.rich」のようなドメイン名を買ってみてはいかがですか？もちろんお名前.comで購入できますよ！

===[/column]

//footnote[ccTld][Country Code Top Level Domainの頭文字を取ってccTLD。国ごとに日本は.jp、フランスは.fr、アメリカは.usのように割り当てられています。]
//footnote[kumagai][@<href>{https://www.kumagai.com/?eid=718}]

== ICANNがレジストリを決める

TLDが生まれてくる源泉となるレジストリは神のごとき存在で責任重大です。そんな重要なレジストリをどの会社に任せるのか、一体誰が決めるのでしょう？

「君が.jpのレジストリね！」とJPRSを選んだのは誰かというと、ICANN（アイキャン）という組織です。ICANNとはインターネットのIPアドレスやドメイン名などの資源を全世界的に調整・管理する非営利法人です。ここが全ドメインの本当の生産元と言ってもいいかもしれません。

.tokyoや.shopのような新しいTLDを「作ろう！」と決める決定権があるのもICANNですし、TLDごとのレジストリを決めるのもICANNです。余談ですがHTTPが80でHTTPSは443、SSHは22のようなプロトコルごとのポート番号を決めているのもICANNです。

前述の.canonや.toshibaのようなブランドTLDも、ICANNに対して各社が「このブランドTLDを作りたいんです！うちがレジストリになります！」と申請をだして、ICANNが承認することでできあがります。

== 取り扱うTLDはお店が自由に決められる

ところで.catというTLDもあります。スペインのカタルーニャという場所のドメイン名で筆者のような猫好きにはたまらないのですが、残念ながら.catはお名前.comでは買うことができません。なぜでしょう？

なぜかというとそれぞれの卸元（レジストリ）からどのTLDを入荷するか？は、それぞれのお店（レジストラやリセラ）が自由に決められるからです。

お店の方針次第で「うちにくれば.comも.netも.jpも.infoも.mobiもなんでも買えますよ」というお店にもなれるし、「うちは.jpしか扱わないよ」というお店にもなれるので、ゴンベエドメインのようにありとあらゆるTLDを入荷して品揃えを売りにしているレジストラもあれば、品ぞろえを絞っているYahoo!ドメインのようなリセラもあるのです。

最初に「ドメイン」で検索したとき、example.co.jpはYahoo!ドメインでは取扱いなしで買えなかったですよね。これはYahoo!ドメインが「うちでは.co.jpを扱わない」という判断をしたからです。

以上がレジストリ、レジストラ、リセラの関係でした。

== 「ドメイン」なのか「ドメイン名」なのか？

ところで、ちょっとここで言葉の整理をしましょう。先ほど、購入のために値段を確認した「example.co.jp」は「ドメイン」でしょうか？それとも「ドメイン名」なのでしょうか？@<fn>{differences}結論から言うと、「example.co.jp」はドメイン名です。

//footnote[differences][初版を書いたときは2つの違いが分かっておらず、ドメインもドメイン名もごっちゃに書いていました。書くことによって「分かったつもりになっていた自分」が次々見つかるので、これからもまだまだ「DNSなにも分からない」の谷が来るんだろうなと思います]

たとえば

 * startdns.fun
 * example.co.jp
 * example.jp
 * example.com

というドメイン名があったとき、次の図（@<img>{startDNS3}）のようにexample（3箇所にある）やcoやjpやcomといった個々の名前空間@<fn>{nameSpace}の領域を「ドメイン」と呼びます。@<fn>{domain}それぞれのドメインを「.（ドット）」でつないで一意に識別する「example.co.jp」や「example.com」といった名前がドメイン名@<fn>{fqdn}です。@<fn>{dot}

//footnote[nameSpace][名前空間とは、その中のものが一意な名前を持つ空間のことです。たとえばパソコンのデスクトップ上にある「会議資料」というフォルダ（名前空間）の直下には、「議事録.txt」という名前のファイルは1つしか作れず、同名のファイルをもう1つ作ることはできません。ですが、「会議資料」の中にさらに「全社総会」というフォルダを作ると、そこは別の名前空間なので「議事録.txt」というファイルを作ることはできます。PHPなどのプログラミング言語においても、名前空間は自分が作った関数とPHPの組み込みの関数の名前が衝突してしまうときの解決手段として存在しています]
//footnote[domain][英語のドメイン（domain）を直訳すると「範囲」とか「領域」のことなので、「この領域をドメインと呼ぶぞ！」と言われても「この猫をキャットと呼ぶぞ！」という感じですごくアホっぽいのですが、そうとしか説明できなくて広い気持ちで許されたい]
//footnote[fqdn][より正確に言うとexample.co.jpはFQDN（Fully Qualified Domain Name、日本語だと完全修飾ドメイン名）で、個々のexampleやcoやjpは相対ドメイン名です。「どこ行きたいの？」と問われたときに「大阪府大阪市中央区！」と言うのがFQDNで、大阪府大阪市に居る状態で「中央区！」と言うのが相対ドメイン名というイメージですね]
//footnote[dot][本当はドメイン名の末尾には「ルート」というドメインを表す.（ドット）があるのですが、省略されることが殆どです]

//image[startDNS3][個々の名前空間がドメインで、それぞれのドメインを識別するための一意な名前がドメイン名][scale=0.8]{
//}

これは

 * 東京都中央区
 * 大阪府大阪市中央区
 * 大阪府堺市南区
 * 京都府京都市南区

という住所と大変よく似ています。次の図（@<img>{startDNS2}）のように、先ほどのexampleやstartdnsと同様、中央区や南区と呼ばれるエリアは国内の複数箇所に存在していますが、都道府県からの住所を言えば一意に識別できます。

//image[startDNS2][exampleと同じように中央区は複数箇所にあり、一意に識別するために住所がある][scale=0.8]{
//}

=== サブドメインとは？

このとき、jpというドメイン（領域）に含まれている（インクルードされている）ドメインは、すべて「jpのサブドメイン」と呼ばれます。

次の図（@<img>{startDNS4}）のとおり

 * startdns
 * example
 * co
 * （coの中の）example

といったドメインはすべてjpのサブドメインです。さらにcoの中のexampleはcoというドメインにも含まれているので、「coのサブドメイン」でもあります。

//image[startDNS4][exampleと同じように中央区は複数箇所にあり、一意に識別するために住所がある][scale=0.8]{
//}

それぞれのドメインを一意な名前、つまりドメイン名で呼んで説明すると次のようになります。

 * startdns.jpはjpのサブドメインである
 * example.jpはjpのサブドメインである
 * co.jpはjpのサブドメインである
 * example.co.jpはjpのサブドメインである
 * example.co.jpはco.jpのサブドメインである

ドメイン名を買うと、サブドメインは作りたい放題です！サブドメインを作るたびに、ドメイン名を買ったときのような支払いは発生しません。

== 実際にお名前.comでドメイン名を買ってみよう

では実際に、お名前.com@<fn>{onamae}でドメイン名を買ってみましょう。「お名前.com」で検索してトップページ（@<img>{onamaeTopPage}）を開きます。

//image[onamaeTopPage][お名前.comのトップページ][scale=0.8]{
//}

//footnote[onamae][@<href>{https://www.onamae.com/}]

トップページにある「全ドメイン検索」をクリックして、ドメイン検索の画面（@<img>{menuAdvanced}）を開きます。

//image[menuAdvanced][ドメイン検索][scale=0.8]{
//}

いったん右上の全選択を押してチェックボックスのチェックを外したら、好きな文字@<fn>{underBar}を入力して欲しいTLDにだけチェック（@<img>{selectDomain}）を入れてください。

今回はちゃんとしたサービスで使う訳ではなく、ドメイン名やDNSの仕組みを学ぶことが目的なので1円～30円程度の安いドメイン名で構いません。それから詳細は後述しますが.jpは持ち主の名前がWhoisで出てしまうため、本名をインターネットで公表したくない人にはお勧めしません。

//footnote[underBar][ドメイン名には_（アンダーバー）は使えませんのでご注意ください。英数字や-（ハイフン）は使えます。]

//image[selectDomain][好きな文字を入力してTLDにチェック][scale=0.8]{
//}

筆者は「startdns.〇〇」というドメイン名が欲しいので、startdnsと記入して比較的安い1円～199円程度のTLDにチェックを入れてみました。TLDを1つしか選ばないとそのドメイン名が売り切れだったということもあるので、いくつかチェックを入れた上で「検索」をクリックしましょう。

すると次の画面で「これは買えるよ、これは売り切れだよ」と教えてくれます。どうやらstartdns.bizは売り切れだったようです。選択肢が幾つかある中で筆者は「startdns.fun」を買うことに決めて、funの下にあるチェックボックスにチェックを入れました。（@<img>{selectStartdnsFun}）右側の「選択されたドメイン」に「startdns.fun」だけが表示されています。自分が買おうと決めたドメイン名だけが右側に表示されていることを確認してください。

//image[selectStartdnsFun][.funにチェックを入れると「選択されたドメイン」にstartdns.funが出る][scale=0.8]{
//}

なお記載されいてるのは有効期間1年のドメイン名代ですので、いま買うと1年後に更新タイミングがやってきます。前述のとおり2年目以降はぐっと値段が上がったりしますので、TLDを決めたら更新料金@<fn>{onamaePrice}も確認しておきましょう。購入するドメイン名が決まったら右側の「料金確認へ進む」を押します。

//footnote[onamaePrice][@<href>{http://www.onamae.com/service/d-price/}]

次に表示されるお申込内容の確認画面（@<img>{registOrder}）でとても大切な作業があります。ここでドメイン名代を再度確認するとともに@<b>{「Whois情報公開代行（新規登録と同時なら無料）」にチェックを入れるのを絶対に忘れない}ようにしてください。チェックを入れ忘れて後からWhois情報公開代行を頼もうとすると980円もかかってしまいます。Whois情報公開代行がどういうものなのかは後述します。

//image[registOrder][「Whois情報公開代行（新規登録と同時なら無料）」に必ずチェックを入れる][scale=0.8]{
//}

なお画面下の方で、まるでセットのポテトのように「ご一緒にサーバはいかがですか？」と聞かれますが、今回はサーバの契約は不要ですのでデフォルトの「利用しない」のままで構いません。右側の「初めてご利用の方」に自分のメールアドレスとパスワードを入れたら「次へ」を押してください。ここで@<b>{入力したパスワードはこの後すぐに使用しますのでしっかりメモしておいて}ください。

お名前IDが発行されたら会員情報の登録画面に進みます。@<b>{画面上部に表示されているお名前IDもメモ}しておいてください。（@<img>{inputAccount}）今回は個人として購入しますので種別は「個人」を選択して名前や住所、電話番号、メールアドレスなどを入力します。ドメイン名を買った直後、ここで入力したメールアドレスに対して重要なメールが届きますので@<b>{必ずメール受信が可能なアドレスを入力して}ください。必須になっている箇所をすべて入力したら右側にある「次へ進む」を押します。

//image[inputAccount][会員情報の登録画面でお名前IDを確認][scale=0.8]{
//}

次は支払方法の選択画面（@<img>{payment}）が表示されます。右側の「お申込み内容」に、選択したドメイン名の料金およびWhois情報公開代行（0円）が表示されていることを確認してください。お申込み内容に誤りがなければクレジットカード情報を記入@<fn>{creditCard}して右側にある緑色の「申込む」を押します。

//image[payment][支払方法の選択画面でお申込内容を確認][scale=0.8]{
//}

//footnote[creditCard][クレジットカードの他にコンビニ支払いや銀行振込、請求書払いが可能ですが説明は省略します。]

「ねえ、本当にサーバ要らないの？」というアラート画面（@<img>{needServer}）が出てきますが、本当に不要ですので「申込まない」を押します。

//image[needServer][サーバは不要なので「申込まない」を選択][scale=0.8]{
//}

おめでとうございます！無事に自分のドメイン名が買えたら購入完了画面（@<img>{complete}）が表示されます。先ほど登録したメールアドレス宛てに「[お名前.com]ドメイン登録 料金ご請求／領収明細」というメールも届いていると思いますので確認してください。@<fn>{domainNews}

//image[complete][ドメイン名の購入完了画面が表示された][scale=0.8]{
//}

//footnote[domainNews][お名前.comでドメイン名を買うと毎日何通も「.co.jpのクーポンを発行したよ！」「今ならこんないいドメイン名が空いてるよ！」と広告メールが届くので、購入完了画面の「メールマガジンの確認」の欄にある「お受け取りを希望されないお客様はこちらをご参照ください。」というリンクから「お名前.comドメインニュースの配信停止」を行っておくことをお勧めします。@<href>{https://help.onamae.com/app/answers/detail/a_id/8126/}]

さてめでたくドメイン名が買えたのですが、ここで必ず設定しておかないといけないことが1つあります。

=== 自動更新はオフにしておこう

お名前.comのトップページに戻って、右上の「ドメインNavi ログイン」をクリックしてください。（@<img>{onamaeTopPageAgain}）「ドメインNavi」とはお名前.comの管理画面のことです。ログイン画面（@<img>{domainNaviLogin}）が表示されたら、先ほど発行されたばかりのお名前ID@<fn>{forgetOnamaeId}とパスワードを入力して「ログイン」を押してドメインNaviにログインします。

//footnote[forgetOnamaeId][もしお名前IDをメモし忘れてしまったらドメイン登録したときに届くメールにも記載されています。]

//image[onamaeTopPageAgain][右上の「ドメインNavi ログイン」をクリック][scale=0.8]{
//}

//image[domainNaviLogin][お名前IDとパスワードを入れてドメインNaviにログイン][scale=0.8]{
//}

ログインするとドメインNaviのトップページではなく「ドメイン契約更新」の画面（@<img>{continueContract}）が表示されます。@<fn>{abTest}

//footnote[abTest][2018年2月時点、お名前.comはABテストの最中なのかログインするお名前IDによってドメインNaviの見た目が大きく異なるようです。本著では新しい方の画面を用いて説明しますので、人によってお手元で見ている画面と見た目が一致しないかも知れません。ですが新旧問わずここでやりたいことは同じで「今買ったドメイン名で自動更新をオフにしたい」だけです。]

//image[continueContract][ドメインNavi ドメイン契約更新][scale=0.8]{
//}

「ドメイン契約更新」の画面が表示されるのは、ドメインNaviがログインするたびに「来年の更新をしませんか？」と聞いてくる仕様だからです。ついさっきドメイン名を買ったばかりで有効期限は1年先ですので無視して先へ進みましょう。先ほど買ったドメイン名の設定変更がしたいので、上部のメニューで左から2つ目の「ドメイン」をクリックしてください。

他のページへ移動しようとすると「更新手続きをお忘れではございませんか？（中略）更新が必要なドメインはお早めにお手続きされることをお勧めいたします。」と警告が出る（@<img>{contractRemind}）のでちょっとドキッとしますが、有効期限は1年も先ですので問題ありません。強い気持ちで「更新画面から移動する」を押してください。

//image[contractRemind][ドメインNavi 更新アラート][scale=0.8]{
//}

ドメイン一覧（@<img>{domainNaviDomainList}）を開くと、今買ったばかりのドメイン名（筆者ならstartdns.fun）が表示されます。自分が買ったドメイン名をクリックしてください。

//image[domainNaviDomainList][ドメインNavi ドメイン一覧][scale=0.8]{
//}

ドメイン詳細（@<img>{domainNaviDomainDetail}）が表示されたら「自動更新」という項目を確認してください。きっと「設定済み」になっていると思います。

//image[domainNaviDomainDetail][ドメインNavi ドメイン詳細][scale=0.8]{
//}

「設定済み」の右側にある「自動更新」を押してドメイン自動更新設定（@<img>{domainAutoRenew}）の画面に進みます。

//image[domainAutoRenew][ドメインNavi ドメイン自動更新設定][scale=0.8]{
//}

ドメイン自動更新設定（@<img>{domainAutoRenew}）の画面で「ON」と書かれている箇所をクリックして自動更新を解除します。「自動更新を解除すると、更新忘れによりドメインを失効する恐れがありますのでご注意ください。」と表示されます（@<img>{domainAutoRenewOffNotice}）が構いません。OKを押してください。

//image[domainAutoRenewOffNotice][ドメイン自動更新解除の確認][scale=0.8]{
//}

@<img>{domainAutoRenewOff}のように自動更新がOFFになったら設定変更は完了です。

//image[domainAutoRenewOff][ドメイン自動更新がOFFになったら完了][scale=0.8]{
//}

いまドメインNaviで確認したとおり、購入時のデフォルト設定ではドメイン名は「自動更新がオン」になっています。購入時の設定のまま放っておくと来年も再来年もドメイン名は更新されてクレジットカードからドメイン名代が引き落とされていきます。自動更新は最初にオフにしておきましょう。

「でも大事なウェブサイトならドメイン名の更新忘れを防ぐため、むしろ自動更新にしておくべきじゃないの？」と思われるかも知れません。しかし実は自動更新には恐ろしい落とし穴があるのです。

===[column] 【コラム】類似のドメイン名を確保しておくべきか？

ヤマト運輸や佐川急便といった宅配業者の不在通知などを装って、SMS@<fn>{sms}に書かれたURLから偽サイトに誘導し、個人情報を盗み取る「スミッシング@<fn>{smishing}」というサイバー攻撃@<fn>{cyber}があります。たとえば佐川急便では「sagawa-exp.co.jp」というドメイン名を使用していますが、偽サイトは「sagawa-umo.com@<fn>{umo}」のようなドメイン名です。（@<img>{startDNS1}）

//image[startDNS1][佐川急便の偽サイトを開こうとするとブラウザが警告してくれる][scale=0.8]{
//}

こうしたフィッシング詐欺や、あたかも公式かのように誤認させるサイトによる被害を防ぐ方法の1つに、類似のドメイン名を予め確保しておく、というものがあります。たとえば任天堂株式会社の国内向けオフィシャルサイトで使用しているドメイン名は「nintendo.co.jp」ですが、任天堂では「nintendo.jp」というドメイン名も登録しています。

このように「株式会社イグザンプル」向けにexample.co.jpというドメイン名を登録するとき、その時点で使用する予定がなくてもexample.jpとexample.comを一緒に確保しておく、というやり方はよく見かけます。

ただTLDはたくさんの種類があるため、example.jpとexample.comは確保したけどexample.incは他人に取られてもいいの？example.siteやexample.netは放っておいていいの？というように、いったいどこまで確保すべきなのか、あるいはexample.jpとexample.comすらも本当に確保しておく意味があるのか、は迷うところかもしれません。ドメイン名は登録した分だけお金がかかります。類似のドメイン名すべてを確保しておくのは現実的ではないので、事業の規模や、フィッシング詐欺の対象となるようなサービスなのか否かを考えて決めるのがよいと思います。

フィッシング詐欺に限らず、著名な社名やサービス名をドメイン名に含めることで誤認によってサイトに集客する、あるいは今後使われそうなドメイン名を先に登録して高値での転売を持ちかける、といった不正行為に対しては、ドメイン名紛争処理方針（DRP）@<fn>{drp}という仕組みでも対応が可能です。正当な権利者が申し立てを行い、DRPの紛争処理機関に認められれば、そのドメイン名の登録を取り消したり、権利者に移転したりできます。

===[/column]

//footnote[sms][ショートメッセージサービスの略。宛先に電話番号を指定してメッセージを送れるサービス]
//footnote[smishing][SMSを用いたフィッシング詐欺のこと。SMSとフィッシング（phishing）を組み合わせてスミッシング（Smishing）と呼ばれている]
//footnote[cyber][偽SMSで個人情報狙う「スミッシング」が激化　携帯事業者装い新手口も @<href>{https://www.sankei.com/affairs/news/190415/afr1904150018-n1.html}]
//footnote[umo][言わずもがなですが、偽サイトにはアクセスしないようご注意ください]
//footnote[drp][Domain name dispute Resolution Policyの頭文字を取ってDRPと呼ばれる。ドメイン名の不正な登録や使用によって生じた紛争を解決するための仕組み]

=== ＜トラブル＞ドメイン自動更新の落とし穴

前述のとおりドメイン名は1年ごとに更新されます。対してクレジットカードは基本的に有効期限が5年です。

たとえば、とある広告代理店A社でクライアントB社の新製品サイト用にドメイン名を買ったとします。本来であればきちんと経理を通して請求書払いで購入すべきですが、サービスインまで日もなかったためディレクターのCさんが「後で経費精算すればいいや」と考えて自分の個人クレジットカードで買い、Web制作会社D社とウェブサーバを運用しているE社へ「ドメイン名は買っといたからこれを使って」と伝えました。@<fn>{fiction}

//footnote[fiction][重ねて書いておきますがこのトラブルはフィクションです。登場するA社やCさんなどの人物・団体・名称等は架空であり、実在のものとは関係ありません。]

ディレクターCさんがドメイン名を買った2年後に転職して会社を去り、そこからさらに3年後にCさんのクレジットカードの有効期限が来ました。お名前.comからは再三に渡って「与信に失敗して決済できなかったよ！クレジットカード情報を新しくして！更新しないと期限切れちゃうよ！」というメール@<fn>{remindMail}が届きますが、宛て先は辞めてしまったCさんのメールアドレスなのでA社の人は誰も気づきません。

//footnote[remindMail][ドメイン名の期限が切れる15日前に自動更新をしようと試み、与信に失敗して「[お名前.com\]ドメイン自動更新 与信失敗」という件名のメールが届きます。]

そしてある日ドメイン名の期限が切れて、突然B社の新製品サイトが見られなくなり、お問い合わせメールも届かなくなって一体何が起きた？！と大騒ぎになります。

「サーバが落ちたのか？」「いいや落ちていない！」「調べたらドメイン名の期限切れらしいぞ、早く更新しなければ！」「誰だ？誰がドメイン名を更新してたんだ！」「クライアントのB社か？委託先のD社か？」「いいや、ドメイン名だしサーバを面倒みてるE社じゃないのか？」「それともうちか？」とA社の中はてんやわんやです。

後任ディレクターのFさんが過去のメールをひっくり返して調べた結果、ようやく「ドメイン名は3年前に辞めたCさんが買っていたらしい」と分かりましたが、Fさんは直接Cさんに面識がありません。まして退職直後ならまだしもCさんがA社を辞めてから既に3年が経過していたため連絡を取るまでがまた大変です。Cさんの連絡先を知っている人を探し回ってFさんはなんとかCさんを捕まえましたが、Cさんも既にお名前.comのお名前ID（会員ID）やパスワードを忘れており…失効直後だったらまだ買い戻せたドメイン名は、そうこうしているうちに日にちが経過してまた市場へ売りに出されてしまい、まったく関係のない業者に買われてしまいました。後日、大枚をはたいてなんとかドメイン名を譲ってもらったものの、このトラブルを通してクライアントB社から広告代理店A社への心象はすっかり悪くなってしまいました…。

いかがでしたか？想像しただけで怖いですよね。こんなトラブルを起こさないためにも、ドメイン名の自動更新をオンにするときは慎重に！そして更新のお知らせが届く連絡先のアドレスは個人のメールアドレスではなく、チームのメールアドレスなどにしておきましょう。

=== 【ドリル】連絡先メールアドレスは自分だけでいい？

==== 問題

あなたはとあるスイムウェアブランドのマーケティング担当者です。今年の夏向けに水着キャンペーンサイトを作るので新しくドメイン名を取ることにしました。お名前.comでドメイン名を買うとき、連絡先メールアドレスには何を入れるべきですか？

 * A. 担当者である自分のメールアドレス
 * B. マーケティングチームのメーリングリスト
 * C. 個人情報流出が怖いので「test@example.com」のような適当なメールアドレス

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はBです。ただしIT系の会社では部署編成などで部署そのものがなくなり、部署に紐づいたメーリングリストもなくなってしまうことがままあります。できるだけ長持ちしそうな社内メーリングリストを選びましょう。
本著で買ったドメイン名のように個人利用のためのドメイン名であれば、連絡先メールアドレスも個人のもので構いません。

===[column] 【コラム】ドメイン名は「買う」ものか？

さて、ここまでドメイン名を「買う」と表記してきましたが、ドメイン名は本当に「買う」ものなのでしょうか？ちょっと立ち止まって考えてみましょう。たとえば花屋さんで一輪のガーベラを買ったら、そのガーベラはあなたの物です。あなたの部屋に飾ってもいいし、他の人にあげてもいいし、瓶詰めのハーバリウムにしてメルカリで売っても構いません。ですが先ほどお名前.comで「買った」ドメイン名は、花と同じようにあなたのものなのでしょうか？これからずっといつまでも使えるのでしょうか？

実はドメイン名は「買う」ものではなく、登録申請を出して「登録する」ものです。お名前.comのサイトでも「国内シェアNo.1のドメイン登録サービス」「今すぐドメイン登録！」のように、しっかり「登録」と書かれています。

たとえば「startdns.funというドメイン名を使いたい！」と思ったら、そのドメイン名を「買う」のではありません。レジストラ（お名前.com）を通して、.funというTLDを管理しているレジストリ（DotSpace, Inc.@<fn>{dotSpaceInc}）に対してドメイン名の登録を申請するのです。登録申請を受け付けたレジストリが、内容を確認した上でレジストリデータベースに情報を登録することでドメイン名の登録は完了します。

ドメイン名を登録することで、私たちはそのドメイン名を一定期間使う権利を得ます。登録したドメイン名には有効期限がありますが、期限が切れる前に更新の手続きをすれば引き続き使用できます。有効期間は基本的に1年単位です。細かな規定はレジストラやTLDにもよりますが、複数年の登録もできますので、長く使うことが先に分かっているドメイン名であれば、最初に登録するタイミングで「10年の登録」をしておくことも可能@<fn>{10year}です。

有効期限が切れるとそのドメイン名は使えなくなり、さらに一定期間が経過すると再び誰でも登録できる状態になります。携帯電話の電話番号と同じようなイメージですね。

===[/column]

//footnote[dotSpaceInc][@<href>{https://radix.website/}]
//footnote[10year][複数年の登録をしていたのにレジストラが倒産してしまった、という場合のリスクについては後述します]

== Whoisとは

ところで先ほどドメイン名を購入するとき「Whois情報公開代行（新規登録と同時なら無料）」というチェックボックスにチェックを入れましたが、もしあそこでチェックを入れずに購入手続きを進めていくと「Whois情報を登録してください」という住所や氏名を入力するページが出てきます。

このWhois情報というのは一体何なのでしょう？自宅の住所とか氏名とか、絶対登録しなきゃいけないのでしょうか？

 * A. 絶対登録しなきゃいけない！
 * B. 任意だから登録しなくてもいい

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

正解はAです。Whois情報は絶対に登録しなければいけません。ではその絶対に登録しなければならないWhoisとは何なのでしょう？

Whoisとは、そのドメイン名を所有している組織や担当者の氏名、連絡先（住所・電話番号・メールアドレス）、ドメイン名の有効期限などがインターネットで誰でも見られるサービスのことです。本当にインターネットで誰でも見られます。

Whoisで検索（@<img>{searchWhois}）するとWhois情報を見るためのサイトがたくさん出てきます。でもドメイン名の所有者情報が見られるなんて一体誰がそんなサービスを提供しているのでしょう？

//image[searchWhois][Whoisで検索するとたくさんのサイトが出てくる][scale=0.8]{
//}

Whois検索はレジストリが提供しているサービスです。レジストリ、覚えていますか？ついさっき出てきましたね。TLD1つにつき必ず1つ存在している、唯一の卸元であるレジストリです。思い出せましたか？

レジストリがそのTLDのWhois情報を管理・公開しているのです。

=== JPRS WHOISでドメイン名の所有者情報を見てみよう

たとえば.jpで終わるドメイン名を管理しているJPRSが提供する「Whois情報確認サイト」はこちら（@<img>{jprsWhois}）@<fn>{jprsWhois}です。

//image[jprsWhois][JPRS WHOIS][scale=0.8]{
//}

//footnote[jprsWhois][@<href>{http://whois.jprs.jp/}]

例として検索キーワードに日清カップヌードルの「cupnoodle.jp」を入れて検索（@<img>{cupnoodleWhois}）してみると、cupnoodle.jpのWhois情報が出てきます。登録者名を見れば「cupnoodle.jpというドメイン名の持ち主は日清食品株式会社なんだな」と分かりますし、登録年月日や有効期限を見れば「2001/03/26から使い始めて2020/03/31が次の更新タイミングなんだな」と分かります。

//image[cupnoodleWhois][cupnoodle.jpのWhois情報][scale=0.8]{
//}

このようにWhoisを使えばドメイン名から所有者を調べることが出来ます。それだけではなく逆に所有者名から所有しているドメイン名の一覧を調べることも出来ます。今度は検索タイプのプルダウンを「ドメイン名情報（登録者名）」にして、検索キーワードに「日清食品株式会社」と入れて検索（@<img>{nissinWhois}）してみましょう。DONBEI.JPやCHIKINRAMEN.JPなど日清食品が所有しているドメイン名の一覧が出てきました。

//image[nissinWhois][登録者名が日清食品株式会社のドメイン名][scale=0.8]{
//}

===[column] 【コラム】ドメイン名は大文字小文字の区別をしない

ところでJPRS WHOISのサイトで「cupnoodle.jp」を入れて検索（@<img>{cupnoodleWhois}）してみると、一番上のドメイン名がCUPNOODLE.JPのように大文字になっています。CUPNOODLE.JPではなく、cupnoodle.jpを検索したのになぜでしょうか？

実はドメイン名は大文字小文字の区別をしません。cupnoodle.jpもCUPNOODLE.JPもcUpNoOdLe.Jpもすべて同一のドメイン名です。

ためしに大文字小文字混ぜこぜにした@<href>{https://WwW.cUpNoOdLe.Jp/}をブラウザで開いてみると、ちゃんとカップヌードルのサイトが見られます。特に最近はブラウザが勝手に大文字を小文字に置換してくれるので、たとえば商品パッケージや紙媒体で目立たせるためにURLのドメイン名の部分を全て大文字にしてもサイトには問題なくアクセスできます。

===[/column]

=== Whoisの項目はレジストリごとに微妙に違う

ではプルダウンを「ドメイン名情報」に戻して今度は検索キーワードに「yahoo.com」を入れ、再びドメイン名から所有者名を調べてみましょう。（@<img>{dataNotFound}）

//image[dataNotFound][yahoo.comを検索すると「該当するデータがありません。」と出る][scale=0.8]{
//}

yahoo.comの所有者を検索すると、なぜか「該当するデータがありません。」と出てきました。yahoo.comはちゃんと実在するドメイン名なのになぜでしょう？

なぜならば、このJPRS WHOISというサイトはJPRSが管理・提供している「.jpで終わるドメイン名のWhois情報が検索できるサイト」なので、comやnetといったjp以外のTLDは対象範囲外だからです。

前述のとおりWhoisはそれぞれのレジストリが管理・提供しているサービスです。jpのレジストリはJPRS、comのレジストリはVeriSign Global Registry Services、shopのレジストリはGMOドメインレジストリ、というようにTLDごとにレジストリ＝Whoisの管理・提供者が異なるため、Whois情報検索サイトもTLDごと@<fn>{whoisSite}に別々（@<table>{whoisSiteList}）なのです。

//footnote[whoisSite][正確にはTLDごとではなくレジストリごとに別々です。たとえばVeriSign Global Registry Servicesはcomとnetのレジストリなので、VeriSign Global Registry Servicesのサイトではこの2つのTLDのWhoisを確認できます。]

//table[whoisSiteList][TLDごとのWhois情報検索サイト]{
TLD	レジストリ	Whois情報検索サイト
------------------------------------
jp	JPRS（日本レジストリサービス）	@<href>{http://whois.jprs.jp/}
com	VeriSign Global Registry Services	@<href>{https://www.verisign.com/ja_JP/domain-names/whois/}
net	VeriSign Global Registry Services	@<href>{https://www.verisign.com/ja_JP/domain-names/whois/}
shop	GMOドメインレジストリ	@<href>{http://whois.nic.shop/}
//}

Whoisを調べたいときTLDごとにサイトがばらばらなのは面倒だな、と思った方は、TLDに関わらずどのドメイン名でも調べられるaguse.jp（@<img>{aguse}）@<fn>{aguse}というサイトがおすすめです。ですがaguse.jpでは各レジストリのWhoisサイトほど詳しい情報は出てこないですし、更新されたWhois情報もすぐには反映されません。最新のWhois情報を全部正確に知りたい！というときは、やはり先ほどのようなレジストリのサイトか、この後@<chapref>{dig}で説明するWhoisコマンドを叩いて確認しましょう。

//footnote[aguse][アグスジェーピー @<href>{https://www.aguse.jp/}]

//image[aguse][どのドメイン名でもWhoisが調べられるaguse.jp][scale=0.8]{
//}

管理がレジストリごとに分かれているため、Whoisはフォーマットが統一されておらず、登録しなければいけない氏名や住所といった項目もレジストリによって微妙に異なります。またWhoisに登録した情報は誰でも見られるため「あなたが持っているドメイン名はもうすぐ有効期限が切れるからここに$30振り込んで！」のような英語の詐欺メールが届くこともままあります。

このようにWhoisには「フォーマットが統一されていない」「詐欺業者に悪用される」などの問題があるため、最近は次世代WHOISと呼ばれるRDAP@<fn>{rdap}への移行が提唱されています。

//footnote[rdap][Registration Data Access Protocolの略。詳しくは@<href>{https://blog.nic.ad.jp/blog/rdap-intro/}を参照。]

=== Whoisを正確に登録しなければいけない理由

まとめるとWhoisとは、そのドメイン名を所有している組織や担当者の氏名、連絡先（住所・電話番号・メールアドレス）、ドメイン名の有効期限などがインターネットで誰でも見られるサービスのことでした。

そして前述のとおりWhois情報は基本的に「正確に登録しなければいけない」もの@<fn>{whyWhois}です。

//footnote[whyWhois][厳密にはTLDによって方針が少しずつ異なります。]

でも個人情報は保護！住所や氏名が漏洩したらすぐにお詫びのクオカード！というこのご時世に、なぜドメイン名の持ち主の情報をインターネットで全公開させているのでしょう？

それはトラブルが発生したときにインターネットの利用者同士が連絡しあって、自律的にトラブルを解決できるようにするためです。トラブルというのは、たとえば「あなたが持っているドメイン名は我が社が商標登録しているブランドの名前です。30日以内に譲渡しなければ不正競争防止法に基づいてドメイン名の使用停止を求める裁判を起こします」というようなものです。

Whois情報がちゃんと登録されていなかったり、あるいは更新されずに古いままになっていたりするとドメイン名の持ち主に連絡ができませんよね？みんなが「このドメイン名の持ち主に連絡取りたいんだけど、持ち主だれ？」といちいちレジストリに問い合わせをしていたらレジストリはてんてこまいです。なのでICANNは各レジストラに対して「最低年1回は登録者にWhois情報を最新化してもらうように！」という確認を義務付けています。

Whoisに情報を登録しなかったり嘘の情報を登録したりすると、場合によってはドメイン名の登録を抹消されてしまいます。ドメイン名を買ったらWhois情報はきちんと登録してください。

=== ＜トラブル＞ドメイン情報認証メールを無視して全サイトが停止

各レジストラはWhois情報をちゃんと登録してもらうために様々な取り組みを行っています。

たとえばお名前.comの場合、ドメイン名を新たに買ったりWhois情報を変更したりした場合、Whoisに登録されたメールアドレスが正しいものか確認するため、登録したメールアドレス宛てに「ドメイン情報認証」というURL付きメール（@<img>{verifyMail}）が飛んできます。そして2週間以内にメール本文中の認証URLを踏まなかった場合、ドメイン名が利用停止になってしまいます。

//image[verifyMail][正しいメールアドレスか確認するためのドメイン情報認証メール][scale=0.8]{
//}

先ほどお名前.comでドメイン名を買ったあなたのところにも「【重要】[お名前.com] ドメイン 情報認証のお願い」という件名のメールが飛んできている@<fn>{limitation}と思います。

本文中の「ドメイン登録者情報のメールアドレスとして情報が正しい場合は、期日までに以下URLへアクセスしてください。」の下に書かれたURLを踏むと「メールアドレスの有効性認証フォーム」という画面（@<img>{verificationMailAddress}）が表示されます。URLを踏んでこの画面が表示されればあとは特に何もしなくて大丈夫です。

//footnote[limitation][ドメイン情報認証はメールアドレス1つにつき1回しか行われません。1つのお名前アカウントで複数回ドメイン名を購入して、いずれもWhoisにはexample@example.co.jpを登録した場合、正確性確認のメールが送られてくるのは最初の1回のみです。またまったく別のお名前アカウントでドメイン名を購入した場合も、Whoisに登録したメールアドレスが既に認証を済ませていれば正確性確認のメールは送られてきません。]

//image[verificationMailAddress][メールアドレスの有効性認証フォーム][scale=0.8]{
//}

繰り返しになりますが、このURLを踏まないまま2週間が経つとドメイン名は利用停止になります。しかも今回買った（あるいはWhois情報を更新した）ドメイン名だけでなく、Whoisに同じメールアドレスを登録している全てのドメイン名が同時に利用停止となりますので注意が必要です。お名前.comでドメイン名を買ったらこの2つを忘れずに行いましょう。

 * Whois情報をきちんと登録する
 * ドメイン情報認証のメールでURLを踏んで正確性確認を行う

=== 【ドリル】Whoisに登録すべきなのはクライアントの情報？

==== 問題

とある化粧品メーカーA社のウェブサイトで使うドメイン名を、広告代理店のB社が代わりに買って、さらにサイトの制作や運用はA社からWeb制作会社のC社に委託した場合、Whois情報にはA社・B社・C社のどれを登録すべきでしょうか？

 * A. A社のウェブサイトなんだからA社を登録すべき
 * B. A社から任されてドメイン名を買ったのはB社だからB社を登録すべき
 * C. 実際にサイトの管理を任されているのはC社だからC社を登録すべき

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はAです。A社のウェブサイトですので基本的にはA社（クライアント）の情報を記載すべきです。Whois情報は誰でも見られるため、広告代理店のB社やWeb制作会社のC社が請け負っていることを公にしてはいけないような守秘義務のあるケースでうっかりWhoisがB社やC社になっていると、見る人が見れば「A社のサイトはB社やC社が関わっているんだ」と分かってしまいます。@<fn>{whyKaisan}

//footnote[whyKaisan][2014年にNPO法人が小学4年生になりすまして作った「#どうして解散するんですか？」というサイトも、WhoisからNPO法人が関わっていることが明らかになって炎上していました。@<href>{http://nlab.itmedia.co.jp/nl/articles/1411/24/news015.html}]

一方でWhois情報は前述のとおりトラブルがあったときの連絡先として公開されているものなので、実際何かトラブルがあればそこに連絡が来ます。先ほどの2週間無視したらドメイン利用停止になる「ドメイン情報認証」のメールも、Whoisのメールアドレス宛に送られてきます。またSSL証明書を購入するときにもWhoisの連絡先に対して「このドメイン名のSSL証明書を発行していいですか？」という確認メールが届きます。あるいはドメイン名の管理をB社から別の広告代理店D社へ移管するようなときにも「D社に移管していいですか？」という確認メールが届きます。

クライアントであるA社にそうした技術的な問い合わせや連絡が来ても困ってしまう…という場合は社名や担当者名などはA社にしておいて、メールアドレスだけはA社に作ってもらったメーリングリスト（メンバーにB社やC社が入っている）にするのが得策でしょう。

=== プライバシーを守るためのWhois情報公開代行

仕事の場合は前述のようにWhoisに正しい情報を登録すべきですが、個人でドメイン名を買ったとき自宅の住所や名前をWhoisに載せるのは抵抗があります。そこで「プライバシーを守るため個人情報をWhoisに載せたくない」という人のためにあるのが、先ほど出てきた「Whois情報公開代行」というサービスです。

これはWhois上で表示される組織名や連絡先を代理でお名前.comの情報にしてくれるサービスで、一般的にはプロキシサービスやプライバシーサービスと呼ばれています。Whois情報公開代行を使えば、Whoisの所有者の欄には自分の名前の代わりに「Whois Privacy Protection Service by onamae.com」と出るので個人情報を晒さなくて済みます。

実際に筆者のstartdns.funのWhois情報を検索（@<img>{startdnsWhois}）してみると、持ち主の情報が「Whois Privacy Protection Service by onamae.com」になっていることが確認できました。あなたもレジストラのWhois情報検索サイトで、自分が買ったドメイン名のWhoisを確認してみてください。

//image[startdnsWhois][startdns.funのWhois情報を見るとお名前.comになっている][scale=0.8]{
//}

ただしjpドメイン名はレジストリであるJPRSの方針として、レジストラによるWhois情報公開代行を「登録者名」を除いて許可しています。そのためお名前.comで.jpのドメイン名を買ってWhois情報公開代行を頼んだ場合、登録者名だけはWhois情報公開代行が適用されずに自分の氏名が表示されてしまいます。

その代わりドメイン名を買った人がレジストラを通してJPRSに「登録者名を非表示にして欲しい」という申請@<fn>{whoisConcealment}を出せば、JPRS側でWhoisの登録者名を「登録者からの申請により非表示」のようにしてくれるのですが、残念ながらお名前.comではドメイン名を買った人からJPRSに対する「登録者名非表示の依頼代行」を受け付けていません。そのため結論としてはお名前.comで.jpのドメイン名を買った場合、Whoisの登録者名に自分の氏名が出てしまうのは回避できない、という状況になっています。

//footnote[whoisConcealment][@<href>{https://jprs.jp/about/dom-rule/whois-concealment/}にある通り、登録者名非表示の申請は必ずレジストラを通して行う必要があり、ドメイン名を買った人から直にJPRSへ申請することはできません。]

=== ＜トラブル＞レジストラが倒産したらドメイン名はどうなる？

レジストラが倒産すると、そこが取り次いでいたドメイン名の管理は他のレジストラへ移転されます。たとえば2006年に有限会社愉快堂出版というレジストラが倒産した際は、業務が完全に停止する前にJPRSによってJPドメイン名の管理が別のレジストラ（株式会社ヒューメイアレジストリ）へと移されました。@<fn>{yukai01}@<fn>{yukai02}

//footnote[yukai01][有限会社愉快堂出版をJPドメイン名管理指定事業者としていた皆様へ 管理指定事業者変更に関するお知らせ @<href>{https://jprs.jp/termination/20060814.html}]
//footnote[yukai02][有限会社愉快堂出版をご利用のJPドメイン名登録者の皆様へ 管理指定事業者からのご案内について @<href>{https://jprs.jp/termination/20061228.html}]

愉快堂出版でドメイン名を登録していた人たちには、移管先のレジストラであるヒューメイアレジストリから「ドメイン名の登録維持を希望されるお客様につきましては、当社での更新手続きが必要となります」という連絡が行われたのですが、このとき貧乏くじを引いた状態になってしまったのは「愉快堂出版でドメイン名を複数年契約していた人たち」でした。

前述のとおり、ドメイン名は複数年の登録・更新が可能です。ですがJPRSのようにレジストリが最長1年の登録・更新しか受け付けていない場合、ドメイン名を使う人とレジストラの間で「10年」の契約を結び、10年分の登録料を支払っていても、実際はその裏側でレジストラが毎年1年ずつ更新の手続きを行っている、ということがあります。この場合、もし2年目の途中でレジストラが倒産してしまったら、ドメイン名を買った人は「10年分の登録料を払ったので、この先まだ8年は放っておいても大丈夫！」と思っていても、管理を引き継いだ新しいレジストラは残り8年分の料金を受け取っておらず、もちろんレジストリも「1年目、2年目の登録料しかもらっていない」という状態になります。

愉快堂出版のケースでもこの事象は発生しました。このときヒューメイアレジストリが出したお知らせ@<fn>{humeia}の抜粋は次のとおりです。

//footnote[humeia][@<href>{https://web.archive.org/web/20070102174302/http://www.reg.humeia.co.jp/topics/yukaido20061228.html}]

//quote{
すでに有限会社愉快堂出版にて複数年の契約を行っている場合でも、当社ではその状況を確認できず、有限会社愉快堂出版から当社への更新手続きも行われていないため、当社にてお客様と有限会社愉快堂出版との契約期間を保障することはできません。
当社にて保障いたします期間は、先述のWhoisにてご確認いただけます期間に加え、今回更新費用をいただいて更新する1年分のみとなります。ご了承ください。
//}

10年分の登録料を先に支払った人たちにしてみれば「そんな！一度払ったのにまた払うの？！」と思われるかもしれませんが、レジストリに払われるべき費用を預かっていた愉快堂出版は倒産してしまい、また移管先のヒューメイアレジストリに責がある訳でもないので仕方がないことです。

これは国内のレジストラ及びレジストリでの話だったので、まだ日本語で情報が得られただけマシだったかもしれません。海外のレジストラやリセラでドメイン名を購入して、そこが倒産してしまったら、移管先のレジストラとは外国語でやりとりすることになります。さらにWhoisにプライバシーサービスを使っていたような場合は、倒産したレジストラから移管先のレジストラに対してドメイン名の契約者情報がきちんと渡されるのか？も心配です。絶対倒産しないレジストラの見分け方は分かりませんが、ある程度信頼のできるレジストラを選びたいものです。

== co.jpは国内企業しか買えないドメイン名

ところでお名前.comで〇〇.co.jpを購入しようとすると「CO.JPドメインご登録条件確認」という確認画面（@<img>{coJpCheck}）でドメイン名を購入するための条件が表示されます。

//image[coJpCheck][CO.JPドメインご登録条件確認][scale=0.8]{
//}
 
画面で確認されているとおり、次の2つの条件を満たさなければ〇〇.co.jpのドメイン名を購入することはできません。

 * 日本国内で法人登記をしている会社、もしくは登記予定・登記申請中の会社であること
 * 同一法人組織で既に属性型JPドメイン名（co.jp、or.jp、ac.jp、go.jp）を取得していないこと

さらに後日、申請書と印鑑証明書を郵送しなければなりません。こうした条件があるのは〇〇.co.jpだけではありません。たとえば〇〇.ac.jpは日本国内の学校法人しか取得できませんし、〇〇.go.jpは日本の政府機関しか取得できません。そもそも.jpで終わるドメイン名は、日本国内に住所を持つ組織・個人・団体しか取得できないのです。

すべてのドメイン名でこうした条件があるわけではありません。取得条件が一切ないドメイン名や、あるいは条件はあるが購入時に特に確認されないため実態としては誰でも購入できるドメイン名などもあります。よく見る一般的な.comや.netや.bizなどのgTLDは、どこの国の誰でも無条件で購入できます。

=== 【ドリル】.co.jpドメインは2つ買える？

==== 問題

あなたはとあるソーシャルゲームの開発会社の情シス担当です。コーポレートサイトや会社のメールアドレスでは〇〇.co.jpというドメイン名を使用しています。この度、社運を賭けた「△△」というブラウザゲームの開発が決まり、社長から「このゲームでは△△.co.jpというドメイン名を使いたい」と言われました。〇〇.co.jpを保持したまま、新たに△△.co.jpドメイン名を買うことは可能でしょうか？

 * A. 〇〇.co.jpを保持したままでは△△.co.jpを買えない
 * B. 〇〇.co.jpを保持したまま△△.co.jpを買える


//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はAです。企業向けの.co.jpや大学向けの.ac.jpなど、組織の種類ごとに用意されている属性型JPドメインは基本的に1つの組織につき1つしか登録できません。ただしこの「1組織1ドメインのみ」という原則は以前は絶対でしたが現在は緩和されています。2014年に「属性型（組織種別型）・地域型JPドメイン名登録等に関する規則」が改訂され、企業の合併・組織名変更・事業譲渡などに限って、JPRSに「1組織1ドメイン名制限緩和申請」という申請@<fn>{domainRestriction}を出せば1つの組織で複数のco.jpドメインを持てるようになりました。ですが残念ながら今回のケースは単なる社長の思いつきなのでこの制限緩和には当てはまりません。

//footnote[domainRestriction][@<href>{https://jpdirect.jp/organizational/domain-restriction-relaxation.html}]

== ドメイン名の有効期限が切れるとどうなるのか？

お名前.comでドメイン名を購入した場合、ドメイン名の有効期限が切れたその日からは、本来のサイトの代わりに一時的にレジストラ（お名前.com）の広告ページが表示されることがあります。

またドメイン名の持ち主が更新をせずドメイン名の期限が切れて一定期間が経過すると、そのドメイン名は再び市場で売りに出されて誰でも買える状態になります。そのためサイトをクローズした後、期限切れになったドメイン名を第三者が再登録して、アダルト向けのサイトや詐欺サイト、あるいはウイルスをダウンロードさせるようなサイトを開設することがあります。このように誰かが落とした価値のあるドメイン名を、さっと取得して悪用する行為をドロップキャッチと言います。使用実績のあるドメイン名は一度も使われていないまっさらなドメイン名よりも集客力があるため、その価値を狙ってこうしたドロップキャッチが行われることが多いのです。

世の中には再度売りに出されたドメイン名を確実に買えるよう、常に入荷待ちをしているドロップキャッチ専門のレジストラ@<fn>{dropCatch}すら存在しています。

//footnote[dropCatch][@<href>{http://blogs.itmedia.co.jp/mohno/2014/12/re.html}]

=== ＜トラブル＞ドロップキャッチされたイオンシネマ

2015年6月、イオンシネマ@<fn>{eaonCinema}のトップページに「【重要なお知らせ（ご注意）】 当社HPへアクセスされる場合、旧ドメインはご利用にならないようご注意ください。」というお知らせが出ていました。

//footnote[eaonCinema][@<href>{http://www.aeoncinema.com/}]

どうやら2013年7月にワーナーマイカルシネマズがイオンシネマに統合された後、旧ドメイン名（warnermycal.com）を手放したら、まんまと業者にドロップキャッチされてしまったようです。ドメイン名を手に入れた業者が「あなたのコンピュータでウイルスが検出されました」系の詐欺サイトを開設し、これはあくまで推測ですが「ワーナーマイカルシネマズのサイトを見ようとしたエンドユーザ」が詐欺サイトへアクセスして何かしらの被害が出てしまったので、注意喚起としてこのお知らせを出したようです。

Internet Archive Wayback Machine@<fn>{archive}で見る限り、2013年7月にサイトをクローズした後も、1年以上はイオンシネマのサイトへリダイレクトをかけていたようです。しかしサイトクローズから1年半以上経った2015年3月頃に旧ドメイン名を手放したところ、直後の4月にドロップキャッチされたものと思われます。

//footnote[archive][@<href>{https://web.archive.org/web/*/http://warnermycal.com}]

サイトクローズの直後に手放した訳ではないので、一応「ドメイン名をすぐには手放さず新サイトへリダイレクトさせよう」という配慮はしていたようです。ですがサイト統合から1年半以上が経って「もうそろそろいいだろう」と手放した結果、このトラブルを招いてしまいました。もう存在しないサイトのドメイン名に毎年更新料を払うのは馬鹿らしい気もしますが、ドメイン名を手放した結果、エンドユーザから「サイトにアクセスしたら変なページが表示された！」とクレームが来て、状況を調査しトップページにお知らせを掲示してお詫びをして…といった対応をする人件費を考えたら、あと何年かはドメイン名を持ったままの方が安かったのではないか、と思います。

=== 【ドリル】ドメイン名を手放してよい条件は？

==== 問題

あなたはとあるスイムウェアブランドのマーケティング担当者です。昨年夏に作った水着キャンペーンサイトで使っていたドメイン名の有効期限が、1年弱経ってもうすぐ切れてしまいます。キャンペーンはとっくに終わっているので、いつサイトが見えなくなっても構いません。また今年の夏向けのキャンペーンサイトは別のドメイン名で作りました。ドメイン名は更新しなくていいでしょうか？

 * A. 大丈夫！更新しません
 * B. 更新しないとダメかも知れない…サイトの状況を確認しよう

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はBです。状況を確認しないことには、手放しても大丈夫なのか更新しなければならないのか判断ができません。

前述のとおり、ドメイン名を手放すとドロップキャッチされて詐欺サイトなどを開設されることがあります。このとき自社のコーポレートサイトから、クローズしたキャンペーンサイトへのリンクがうっかり残っていると、「おたくのサイトで『キャンペーンサイトはこちら』というリンクを踏んだらアダルトサイトにつながって架空請求されたんだけど！どういうこと？！」とエンドユーザからクレームが来ることも考えられます。

キャンペーンが終わった後も、検索結果やニュースサイトの古い記事から流入してきたり、ブックマークで直にサイトを開いたり、というアクセスは少なくありません。そもそもキャンペーンが終わった後は、アクセスしてきた人を自社のコーポレートサイトや翌年のキャンペーンサイトなどにきちんとリダイレクトさせて誘導してあげましょう。

このとき、HTTPステータスコードは「302 Moved Temporarily（一時的な移動）」ではなく「301 Moved Permanently（恒久的に移動）」にしておくことが大切です。ステータスコードを301にしていればブラウザ側がリダイレクトをキャッシュしますので、2回目以降は旧サイトにアクセスしようとした時点で新サイトへ即リダイレクトされるようになります。

その状態でドメイン名の有効期限が近付いてきたら、アクセスログなどで「クローズ後のサイトへアクセスしてきている人がもうほぼいないこと」を確認した上で、さらにコーポレートサイトといった自社の他サイトから、クローズしたサイトへのリンクが残っていないかも確認します。アクセスもほぼないしリンクも残っていなければ、最終的に「ドメイン名がドロップキャッチされても構わないか」を社内で確認して、ドメイン名を手放しても本当に問題ない、と判断できたら手放すようにしましょう。

ドメイン名の更新代はおおよそ数百円から高くても数万円程度です。確認をせずうかつに手放すと、被害をこうむったユーザからの問い合わせで「ドメイン名更新代＜人件費」になることも十分あり得ます。どうしても判断がつかなければ更新してしまった方が安全と言えるかもしれません。

== ドメイン名を買ったらサイトが見られるか？

ドメイン名も買ったしWhois情報も登録しました。でもまだDNSの設定は何もしていません。この状態だと何が表示されるのか、ブラウザで自分のドメイン名のサイトを見てみましょう。（@<img>{onamaeCm}）

//image[onamaeCm][http://自分のドメイン名/を開くとお名前.comの広告が出る][scale=0.8]{
//}

なぜこのページが表示されるのか？は、@<chapref>{whatIsDns}で紐解いていきましょう。
