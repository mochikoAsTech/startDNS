= トラブルシューティング

ドメインやDNSの周りには「知ってさえいればすぐ解決できるけど、知らないとどうにもならない」という落とし穴がいくつかあります。
この章ではそんなありがちトラブルとその解決方法、あるいは未然に防ぐための対策をご紹介していきます。

//pagebreak

== ＜トラブル＞URLはwwwありなしどっち？

サイトのドメインをwwwありかなしかはっきり決めておかなかったことで、商品パッケージではwwwなし、店頭で配るチラシにはwwwありのURLを記載してしまい、wwwありとなしのURLがあちこちで混在してしまった・・・というトラブルはよくあります。

「え、別にwwwあるかないかくらい些細なことじゃないの？何かだめなの？」と思われるかも知れませんが、これは意外と重要な問題です。

そもそもドメインをwww.example.co.jpのように頭（第4レベルドメイン）から最後（トップレベルドメイン）までしっかり全部書いたものをFQDN@<fn>{fqdn}と呼びます。

 * www : 第4レベルドメイン
 * example : 第3レベルドメイン
 * co : 第2レベルドメイン
 * jp : トップレベルドメイン

//footnote[fqdn][Fully Qualified Domain Nameの略で、日本語にすると完全修飾ドメイン名。正確を期するのであればFQDNにはTLDであるjpまでではなく、さらにルートを表す.（ドット）も含むべきですが、ここではTLDまで表記されていればFQDNとします。余談ですがFQDNに対して、wwwやwww.exampleのように一部を抜き出した表記は相対ドメイン名、あるいは不完全なドメイン名と呼びます。]

startdns.funとwww.example.co.jpは全く別のFQDNです。それと同じようにwww.example.co.jpとexample.co.jpも全く別のFQDNです。

名前が途中まで一緒だとなんだか近しいような気がしてしまいますが、北海道と奄美大島が全く別の場所であるのと同様に、地名が似ていても奄美大島と大島もまったく別の場所@<fn>{oshima}ですよね。

//footnote[oshima][大島は伊豆諸島にあり東京から船で30分、対して奄美大島は沖縄の近くにあります。]

たとえば実際に用意したウェブサイトはwww.example.co.jpなのに、LINEのプッシュ通知で「今すぐexample.co.jpにアクセス！」と告知してしまったとします。これはイベント会場が奄美大島にあるのに「大島（東京）でイベントやります！」と告知してしまったようなものなので、LINEを見たユーザがURLをクリックしてexample.co.jpにアクセスしてもこのままではサイトは表示されません。

気の利いたWeb制作会社であれば、依頼側が何も言わなくてもドメインやリダイレクトの設定をしておいてくれて、example.co.jpを訪れたユーザを取りこぼさずにwww.example.co.jpにリダイレクトさせておいてくれるかも知れませんが、そうでなければ折角の告知が台無しです。（「リダイレクトの設定」というのは、大島に「奄美大島への自動転送装置」を設置しておくようなものだと思ってください）

また「うちのサイトはwwwありとなしのどちらでアクセスしても同じ画面が出るよ！リダイレクトはされないけどね」という場合もやはり問題です。検索エンジンはFQDNが異なるサイトを全く別のサイトとして認識するため、wwwありのサイトとなしのサイトでドメインとしての価値が分散されてしまい、その結果として検索時に上位表示されにくくなります。

サイトを作るときは、最初にFQDNをwwwありなのかなしなのかはっきり決めましょう。もし既にばらばらの状態でサイトが公開されてしまっていたら、今からでも「メインをwwwありにする」のように決めて、片方にちゃんとアクセスを寄せるようにしましょう。wwwありでもなしでも正直どっちでもいい、という場合は、前述の「ZONE APEXではCNAMEが使えない」問題があるため、将来CDNを使いたくなった時に弊害がないようwwwありにしておくのがお勧めです。

== ＜トラブル＞.devで終わるテストサイトが見られなくなった

2017年12月、.devで終わるドメインのサイトをChromeで開くと、強制的にHTTPからHTTPSにリダイレクトされるようになり、あちこちで「テストサイトが見られなくなった！」「開発環境が急に使えなくなった！」という悲鳴が上がりました。

もともとgTLDは.comや.netなどの22種類しかなく、.devというTLDは存在しなかったため、IT系の各社が組織内のネットワーク（開発環境など）でオレオレTLDとして勝手に.devを使っていた、という背景がありました。しかしgTLDの種類が段々増えてきてとうとう.devというTLDもできてしまい、色んなところで「まずいぞ、名前衝突(Name Collision)する・・・」という話題が出たのが2014年ごろのことでした。

ちなみに余談ですがICANNWiki@<fn>{icannWiki}によると、この.devは当初AmazonとGoogleで「俺がレジストリになる！」「いいや、俺がなる！」と奪い合ってたけれど、.youと.talkをAmazonに譲って、代わりに.devをGoogleがゲット、というような経緯があったようです。

詳しくは@<chapref>{domain}でお話ししたとおりですが、レジストリとはそのTLDの唯一の卸元ですので、あちこちで「Googleが.devを買った」と言われているのは、この「Googleが.devのレジストリになったこと」を指しているものと思われます。

//footnote[icannWiki][@<href>{https://icannwiki.org/.dev}]

そして今回Googleが「Chromeで.devを開くと強制的にHTTPSにリダイレクトする」という暴挙に出たのは「Googleは2014年にdevのレジストリ（生産元）になった。でもまだ.devのドメインは一般発売していない。ということは今.devを使っている人は全員、ドメイン買わずに勝手に使ってる人なので迷惑が掛かっても知ったことではない。だから.devはHTTPSに強制リダイレクトさせるね」ということなんだと推察しています。

.devだけなく.appというTLDも同様のようですので、これらのドメインがもうHTTPSでしか使えないということは、Googleは.devを.comや.netのように普通に売るのではなく、何か特別な用途で使わせるつもりなのではないか、と思われます。

このトラブルについては「.devが使えなくなったからとりあえず.testにした！解決！」のような記事も見ますが、なんで.testにしたら直ったのか？.testでいいならたとえば.dev2でもいいのか？といった根本原因と解決策が分かっていないとまた同じトラブルが起きてしまいます。

ざっくり言うと、.testはいいけど.dev2はだめです。社内ネットワークにしてもテスト用のメールアドレスにしても@<chapref>{dig}で書いたとおり例示やテストで使っていいドメインが用意されているので、基本的にはそれを使いましょう。「自分の持ち物でないドメイン」を勝手に使うのは、今回のようなトラブルの元です。

== サイト移管のAtoZ

自社サイト（example.net）はWeb制作会社のA社にお任せしていたが、サイトリニューアルを機に運用をA社からB社に移管することになった。でも移管と言っても何をすればいいのかふんわりしていてよく分からない・・・。そんなときは以下のような移管前後の表（@<table>{domainTransfer}）を作って埋めていきましょう。

//table[domainTransfer][サイト移管前後表]{
　	移管前	移管後
------------------------------------
1.ドメインの管理	A社	B社
2.お店（レジストラ・リセラ）	お名前.com	お名前.com
3.ネームサーバ	お名前.com	Route53
4.ウェブサーバ	A社のクラウドサーバ（203.0.113.111）	EC2（203.0.113.222）
//}

@<table>{domainTransfer}のようにドメインの管理はA社からB社に変わるけれど、レジストラはお名前.comのまま変わらないのであれば、お名前.comの「お名前ID付け替え」という機能でA社のお名前IDからB社のお名前IDにドメインを移動することができます。

ドメインの管理がB社に移ったらお名前.comのネームサーバにあったリソースレコードをRoute53にコピーして、ドメインNavi（お名前.comの管理画面）でネームサーバをRoute53に変更します。仮にサイトリニューアルが5月1日だったとしたら、これらの作業は4月中に済ませておきましょう。この時点ではまだ移管前のウェブサーバを使っています。

EC2上でリニューアル後のサイトが完成してテストも完了したら、5月1日にB社がRoute53でexample.netのAレコードの値を203.0.113.111から203.0.113.222に書き換えてやればサイト移管は完了です。

このようにドメインの管理→ネームサーバ→ウェブサーバの順で移管することで、移管元のA社の負担が少なくなり、移管先であるB社が主体となって移管作業を進められるようになります。逆の順番（ウェブサーバ→ネームサーバ→ドメインの管理）で移管を進めようとすると、5月1日のAレコード書き換えもB社からA社に頼まなければならないし、お名前.comのネームサーバにあるリソースレコードの情報もいちいちA社がB社に渡してあげないといけません。

=== 【ドリル】リニューアル後のサイトが人によって表示されない

==== 問題

ドメインの管理やネームサーバの変更は4月上旬に済ませたし、EC2上で動いている新サイトもテストはばっちりです。5月1日のサイトリニューアル当日、B社のCさんはRoute53でexample.netのAレコードの値を203.0.113.111から203.0.113.222に書き換えた後、手元のスマホでサイトを開いてリニューアル後のページが正しく表示されることを確認してからクライアントに「リリース完了」の電話をしました。ですが電話の向こうのクライアントは「え、古いサイトが表示されるんですけど・・・？」と困惑気味です。

慌ててパソコンのブラウザでサイトを見ると、確かにリニューアル前の古いサイトが表示されました。別のオフィスにいるデザイナーにチャットで「ちょっとサイト見てくれない？古いやつが出てる？」と聞いたところ「こっちではちゃんと新しいサイトが表示されてますよ？」と返事が来ました。

先ほどCさんが書き換えたリソースレコードは以下のようになっていました。

//cmd{
変更前
example.net.    604800  IN  A    203.0.113.111

変更後
example.net.    300     IN  A    203.0.113.222
//}

人や端末によって古いサイトが表示されたり、リニューアル後の新しいサイトが表示されたりする現象の原因は次のどれでしょうか？

 * A. 変更前のTTL（604800）が長いことが原因
 * B. 変更後のTTL（300）が短いことが原因
 * C. 変更後のIPアドレス（203.0.113.222）が間違っていることが原因

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はAです。TTLはTime To Liveの略でキャッシュ保持時間のことです。TTLに書いてある秒数が過ぎるまで、フルリゾルバにはこのリソースレコードがキャッシュとして残ります。

example.netの変更前のAレコードはTTLが604800秒、つまり7日間になっているため、CさんがAレコードを書き換えてからも最大7日間はフルリゾルバに古いIPアドレスがキャッシュされており、そのフルリゾルバを使っているユーザには古いサイトが表示されてしまうのです。

人や端末によって異なるフルリゾルバを使っているため、Cさんのスマホでは新しいサイトが見られますが、クライアントのパソコンではまだ古いサイトが表示されてしまう、といった現象が起こります。古いウェブサーバでリダイレクトの設定をすればいいんじゃない？と思われるかもしれませんが、古いウェブサーバに来たアクセスをexample.netにリダイレクトしたところでまた古いウェブサーバにリクエストが飛んでくるだけですので、何の意味もないどころか無限リダイレクトでブラウザがエラーになってしまいます。

キャッシュが消えるまでの時間を逆算して考えると、そもそもCさんはリニューアル日である5月1日の8日以上前にexample.netのAレコードのTTLを300程度まで短くしておいて、当日IPアドレスを書き換えたらすぐに反映されるようにしておくべきでした。

どうしてもキャッシュを今すぐ消したい！という場合、もしC社の情シスが自社のフルリゾルバを管理しているのであれば「フルリゾルバのキャッシュをクリアして！」と頼めばキャッシュがなくなって、ネームサーバへ改めてリソースレコードを問い合わせに行ってくれますが、それでリニューアル後のサイトが表示されるようになるのはC社内だけの話です。世界中にあるフルリゾルバすべてに対してキャッシュクリアをお願いしてまわるわけにはいかないので、クライアントもC社もキャッシュが消えるまで大人しく7日待つしかありません。

事前にTTLを確認した上で短くしておくことで、無駄に「浸透」を待たなくて済みますし、TTLを過ぎても新サイトに切り替わらなければ何か他に問題があるのでは？と気づくことができます。サイトリニューアル時は変更対象のリソースレコードのTTLを事前に確認しておきましょう。

== ＜トラブル＞サブドメインを追加したのにサイトが見られない

たとえば次のように3つのAレコードがあったとします。

//cmd{
example.net.        300     IN  A    203.0.113.222
www.example.net.    600     IN  A    203.0.113.222
stg.example.net.    900     IN  A    203.0.113.222
//}

この状態でexample.netのAレコードをdigで引いてみると、TTLが300なのでフルリゾルバにはキャッシュが5分間保持されます。www.example.netならTTLが600なので10分間、stg.example.netなら15分間保持されます。

ですが、存在しないtest.example.netのAレコードをdigで引いたら「そんなレコードなかったよ」というキャッシュはフルリゾルバに残るのでしょうか？そして残るとしたらキャッシュ保持時間は何秒になるのでしょう？

実際に自分のドメインで試してみましょう。筆者はstartdns.funを使ってみますので、あなたもお名前.comで買ったドメインを使って試してみてください。

先ずはリソースレコードが存在しないtest.startdns.funをdigで引いてみましょう。statusが「そのドメインのリソースレコードは存在しない」という意味のNXDOMAINになって返ってきます。該当するレコードが存在しないためANSWER SECTIONは存在せず、代わりにドメインの管理情報を表すSOAレコードが付加情報として返ってきました。

//cmd{
$ dig test.startdns.fun a

; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.62.rc1.el6_9.5 <<>> test.startdns.fun a
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NXDOMAIN, id: 16872
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 1, ADDITIONAL: 0

;; QUESTION SECTION:
;test.startdns.fun.             IN      A

;; AUTHORITY SECTION:
startdns.fun.           900     IN      SOA     ns-943.awsdns-53.net. awsdns-hostmaster.amazon.com. 1 7200 900 1209600 86400

;; Query time: 139 msec
;; SERVER: 127.0.0.1#53(127.0.0.1)
;; WHEN: Wed Mar 21 17:59:28 2018
;; MSG SIZE  rcvd: 119
//}

このとき「そんなレコードは存在しない」というネガティブキャッシュがフルリゾルバに残ります。ネガティブキャッシュの保持時間はSOAレコードのTTL、もしくはSOAのMINUMUM（Negative cache TTL）の値のいずれか小さい方となります。

今回のtest.startdns.funの場合、SOAレコードのTTLは900で、SOAのMININUMは86400ですので、ネガティブキャッシュの保持時間は900秒（15分）となります。ではネガティブキャッシュが残っている15分の間にRoute53でtest.startdns.funのAレコードを作ってみましょう。

@<href>{https://aws.amazon.com/} からマネジメントコンソールにログインしたら、左上の「サービス」を押してRoute53を選択します。Route53の画面（@<img>{dnsManagement}）を開いたら左メニューのHosted Zonesを選択します。

//image[dnsManagement][左メニューのHosted Zonesを選択][scale=0.8]{
//}

表示されている自分のドメイン（筆者ならstartdns.fun）を選択（@<img>{selectDomainName}）します。

//image[selectDomainName][自分のドメインを選択][scale=0.8]{
//}

上部にある青い「Create Record Set」を押したら、右側のNameにtest、Valueに203.0.113.222@<fn>{rfc5737}と入力して右下の青い「Create」を押します。

//footnote[rfc5737][このIPアドレスは例示用として定められているIPアドレスです。@<href>{https://tools.ietf.org/html/rfc5737}]

//table[recordSet][レコード作成時の設定]{
項目	入力するもの
------------------------------------
Name	test
Value	203.0.113.222
//}

//image[createRecordSet][NameとValueを記入したら「Create」を押す][scale=0.8]{
//}

これでtest.startdns.funのAレコードが出来上がりました。（@<img>{createdARecord}）

//image[createdARecord][test.startdns.funのAレコードが出来た][scale=0.8]{
//}

それでは再度test.startdns.funをdigで引いてみましょう。今さっきAレコードを作ったので、今度は存在しているはずです。

//cmd{
$ dig test.startdns.fun a

; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.62.rc1.el6_9.5 <<>> test.startdns.fun a
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NXDOMAIN, id: 2854
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 1, ADDITIONAL: 0

;; QUESTION SECTION:
;test.startdns.fun.             IN      A

;; AUTHORITY SECTION:
startdns.fun.           759     IN      SOA     ns-943.awsdns-53.net. awsdns-hostmaster.amazon.com. 1 7200 900 1209600 86400

;; Query time: 0 msec
;; SERVER: 127.0.0.1#53(127.0.0.1)
;; WHEN: Wed Mar 21 18:01:49 2018
;; MSG SIZE  rcvd: 119
//}

Aレコードは存在しているのに再度NXDOMAINが返ってきました。先ほど「そのドメインのリソースレコードは存在しないよ」と言われてから、まだ900秒（15分）が経過していないためネガティブキャッシュが返ってきたようです。このときSOAレコードのTTLを見ると759と表示されています。これはSOAレコードの残りキャッシュ保持時間が759秒であることを示しています。

ではフルリゾルバの中にあるネガティブキャッシュを返すのではなく、もう一度ルートネームサーバから順にちゃんと聞きに行ってもらいましょう。digコマンドに+traceオプションを付けて叩いてみます。

//cmd{
$ dig test.startdns.fun a +trace

; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.62.rc1.el6_9.5 <<>> test.startdns.fun a +trace
;; global options: +cmd
.                       514824  IN      NS      m.root-servers.net.
.                       514824  IN      NS      e.root-servers.net.
.                       514824  IN      NS      d.root-servers.net.
.                       514824  IN      NS      g.root-servers.net.
.                       514824  IN      NS      f.root-servers.net.
.                       514824  IN      NS      a.root-servers.net.
.                       514824  IN      NS      l.root-servers.net.
.                       514824  IN      NS      k.root-servers.net.
.                       514824  IN      NS      b.root-servers.net.
.                       514824  IN      NS      h.root-servers.net.
.                       514824  IN      NS      c.root-servers.net.
.                       514824  IN      NS      j.root-servers.net.
.                       514824  IN      NS      i.root-servers.net.
;; Received 508 bytes from 127.0.0.1#53(127.0.0.1) in 1682 ms

fun.                    172800  IN      NS      b.nic.fun.
fun.                    172800  IN      NS      c.nic.fun.
fun.                    172800  IN      NS      d.nic.fun.
fun.                    172800  IN      NS      a.nic.fun.
;; Received 279 bytes from 2001:7fe::53#53(2001:7fe::53) in 1538 ms

startdns.fun.           3600    IN      NS      ns-1605.awsdns-08.co.uk.
startdns.fun.           3600    IN      NS      ns-177.awsdns-22.com.
startdns.fun.           3600    IN      NS      ns-1072.awsdns-06.org.
startdns.fun.           3600    IN      NS      ns-943.awsdns-53.net.
;; Received 175 bytes from 108.59.161.12#53(108.59.161.12) in 74 ms

test.startdns.fun.      300     IN      A       203.0.113.222
startdns.fun.           172800  IN      NS      ns-1072.awsdns-06.org.
startdns.fun.           172800  IN      NS      ns-1605.awsdns-08.co.uk.
startdns.fun.           172800  IN      NS      ns-177.awsdns-22.com.
startdns.fun.           172800  IN      NS      ns-943.awsdns-53.net.
;; Received 191 bytes from 205.251.198.69#53(205.251.198.69) in 99 ms
//}

+traceを付けたらちゃんと「test.startdns.funに紐づくIPアドレスは203.0.113.222です」という返答が返ってきました。でも+traceを付けて引いた結果はフルリゾルバのキャッシュを上書きしないため、+traceを消すとやはりNXDOMAINの状態に戻ります。ネガティブキャッシュの残り時間はあと334秒です。

//cmd{
$ dig test.startdns.fun a

; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.62.rc1.el6_9.5 <<>> test.startdns.fun a
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NXDOMAIN, id: 19871
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 1, ADDITIONAL: 0

;; QUESTION SECTION:
;test.startdns.fun.             IN      A

;; AUTHORITY SECTION:
startdns.fun.           334     IN      SOA     ns-943.awsdns-53.net. awsdns-hostmaster.amazon.com. 1 7200 900 1209600 86400

;; Query time: 0 msec
;; SERVER: 127.0.0.1#53(127.0.0.1)
;; WHEN: Wed Mar 21 18:08:54 2018
;; MSG SIZE  rcvd: 119
//}

さらに5分ほど待ってようやくネガティブキャッシュの保持時間が過ぎたら、もう一度test.startdns.funをdigで引いてみましょう。statusはNXDOMAINからNOERRORに変わり、ANSWER SECTIONのところにRoute53で設定したAレコードが表示されました。

//cmd{
$ dig test.startdns.fun a

; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.62.rc1.el6_9.5 <<>> test.startdns.fun a
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 64301
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 4, ADDITIONAL: 8

;; QUESTION SECTION:
;test.startdns.fun.             IN      A

;; ANSWER SECTION:
test.startdns.fun.      300     IN      A       203.0.113.222

;; AUTHORITY SECTION:
startdns.fun.           3599    IN      NS      ns-1605.awsdns-08.co.uk.
startdns.fun.           3599    IN      NS      ns-177.awsdns-22.com.
startdns.fun.           3599    IN      NS      ns-1072.awsdns-06.org.
startdns.fun.           3599    IN      NS      ns-943.awsdns-53.net.

;; ADDITIONAL SECTION:
ns-1072.awsdns-06.org.  168458  IN      A       205.251.196.48
ns-1072.awsdns-06.org.  168458  IN      AAAA    2600:9000:5304:3000::1
ns-1605.awsdns-08.co.uk. 168458 IN      A       205.251.198.69
ns-1605.awsdns-08.co.uk. 168458 IN      AAAA    2600:9000:5306:4500::1
ns-177.awsdns-22.com.   168459  IN      A       205.251.192.177
ns-177.awsdns-22.com.   168459  IN      AAAA    2600:9000:5300:b100::1
ns-943.awsdns-53.net.   168459  IN      A       205.251.195.175
ns-943.awsdns-53.net.   168459  IN      AAAA    2600:9000:5303:af00::1

;; Query time: 163 msec
;; SERVER: 127.0.0.1#53(127.0.0.1)
;; WHEN: Wed Mar 21 18:19:03 2018
;; MSG SIZE  rcvd: 367
//}

新たにサイトをオープンするとき、まだリソースレコードが用意できていないのにブラウザでサイトを開いてしまい、リソースレコードが用意できた後で再度確認しようとしたらなぜか見られない・・・という現象はこのネガティブキャッシュが原因です。「もうAレコード用意できたかな？」と確認するときは、ネガティブキャッシュが残っても困らない環境でdigを叩いてみるのがお勧めです。

== ＜トラブル＞CAAレコードが原因でSSL証明書が発行できなかった

最近、SSL証明書を取得するときに「CAAレコード」という言葉を聞くようになってきました。

CAAレコードのCAAはCertification Authority Authorizationの略で、CAAレコードに「そのドメインの証明書を発行できる認証局」を書いておくことで、意図しない認証局による証明書の発行を防ぐ仕組みになっています。

たとえば毎年DigiCertでstartdns.funのSSL証明書を発行をしており、それ以外の認証局に発行を依頼する予定はない、という場合はstartdns.funのCAAレコードでdigicert.comを指定しておくことで、DigiCert以外の認証局に対して証明書の発行依頼があっても認証局は証明書を発行せず、ドメイン管理者に対して意図しない発行申請があったことを報告してくれます。

CAAレコードは必須ではありませんので、CAAレコードを設定していなければ従来通り証明書の発行に際してチェックや制限は一切行われません。ただしCAAレコードが見つからない場合の挙動には注意が必要です。

たとえばwww.example.co.jpの証明書を取ろうとした場合、最初はwww.example.co.jpのCAAレコードがないか確認し、なければexample.co.jpのCAAレコードを確認、それもなければco.jpのCAAレコード、最終的にはjpのCAAレコードまでさかのぼって順に確認していきます。@<fn>{jprsCaa}

//footnote[jprsCaa][ちなみにJPRSではco.jpやjpのCAAレコードは作成しておらず、当面作成する予定もないそうです。]

そのため証明書を発行しようとしたFQDNではCAAレコードを設定していなかったのに、その親ドメインでCAAレコードを設定していたため、予期しない形で証明書の発行が制限されてしまった、というトラブルが予想されます。SSL証明書の発行が思いがけず失敗してしまったときは、そのドメインのTLDまでさかのぼってCAAレコードが設定されていないか確認してみるのがよいでしょう。

== ＜トラブル＞AWSで突然ドメイン名が引けなくなった

AWSのEC2でインスタンスを立てると、自動的にネットワーク内にAmazon DNS@<fn>{amazonDns}と呼ばれるフルリゾルバが用意されます。Amazon DNSはフルリゾルバ、Route53はネームサーバですので全く別物です。

//footnote[amazonDns][正確にはインスタンスを立てたらではなく、VPCを作成するとAmazon DNSはVPCの範囲で第4オクテッドを2にしたIPアドレスで自動的に作成されます。たとえばVPCのIPv4ネットワークの範囲が172.31.0.0/16の場合、Amazon DNSのIPアドレスは172.31.0.2となります。]

このAmazon DNSは、次のように若干変わった挙動をするので注意が必要です。

=== レートリミットを超えるとNXDOMAINを返す

Amazon DNSに対する名前解決の問い合わせのパケット数は「ネットワークインターフェイスあたり最大1024パケット/秒」に制限されています。つまりEC2のインスタンスで大量にdigを叩いて、パケット数が秒間1024パケットを超えると、制限に引っかかってきちんと応答が返ってこなくなるのです。@<fn>{rateLimit}

//footnote[rateLimit][@<href>{https://dev.classmethod.jp/cloud/aws/amazon-dns-threshold-exceeded-action/}]

=== 勝手にTTLを短くする

AWSのEC2でdigコマンドを叩いてみたところ、TTLを1000にしているはずのリソースレコードでTTLが60になって返ってきました。公式ドキュメントでは記載がないのですが、リソースレコードのTTLが60秒以上の場合、Amazon DNSはすべて60秒にして返す@<fn>{ttlShorten}ようです。（逆にリソースレコードのTTLが60秒より短い場合はそのままです）

//footnote[ttlShorten][@<href>{https://dev.classmethod.jp/cloud/aws/dig-route53-begginer/}]

ネームサーバが死んでしまったときのためにTTLを長くしておいたつもりでも、AWSでは他の環境より早くキャッシュが切れて異なる挙動になると思われますので、注意が必要です。
