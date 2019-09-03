=  digとwhoisを叩いて学ぶDNS

性能向上のための格言に「推測するな計測せよ」というものがありますが、障害発生時にも同じことが言えます。DNS絡みのトラブルが起きたとき、あるいはサイトが意図した動作をしないとき、調べ方さえ知っていれば原因を調査できますし「恐らくDNSの浸透が原因じゃないかと…48時間ほど待てば多分…」のようなエンジニアらしからぬ回答をしなくて済みます。

この章ではdigコマンドとwhoisコマンドを実際に叩いて色んなことを調べながら、DNSの仕組みを学んでいきましょう。

//pagebreak

== digとwhoisのインストール

digコマンドやwhoisコマンドを使いたくても、そこにインストールされていなければ使えません。Macにはどちらのコマンドも元々インストールされているので、あなたがMacユーザであればターミナルを起動すればすぐに使うことができます。

CentOSやAmazonLinuxなどのサーバ環境がある人は、そこでrootになって次のyumコマンドを叩けばインストールできます。

//cmd{
digコマンドのインストール
# yum -y install bind-utils

whoisコマンドのインストール
# yum install -y jwhois
//}

=== MacもLinuxのサーバ環境もない場合

パソコンはWindowsだし手近にコマンドを叩けるような環境はない…という方は、Route53を使うために折角AWSでアカウントを作ったので、EC2@<fn>{ec2}でインスタンス@<fn>{instance}を立ててみるのがお勧めです。サーバスペックごとにインスタンスタイプという区分があるのですが、t2.microというインスタンスタイプならアカウント作成から1年間は毎月750時間まで無料で使えます。ここでは詳しく説明しませんが@<fn>{startAws}、AWSのマネジメントコンソールでEC2ダッシュボードを開いて「インスタンスの作成」を押したら、後は画面の表示に従ってぽちぽち選んでいくだけで5分もあればすぐにサーバが作れます。@<fn>{750h}

インスタンス立てるのはちょっと無理！という場合は、@<chapref>{aws}で使った「nslookup(dig)テスト【DNSサーバ接続確認】」@<fn>{cmanUrl3}というページや各レジストリのWhois情報確認サイトで疑似的にdigやwhoisを叩く形で代用しても構いません。

//footnote[ec2][Elastic Compute Cloudの略。AWSにはいろいろなサービスがありますがEC2はいわゆるサーバのことです]
//footnote[instance][AWSではサーバのことをインスタンスを呼びます]
//footnote[startAws][本著の続編である「AWSをはじめよう」にはEC2でインスタンスを立てる手順が詳しく載っています]
//footnote[750h][月に750時間まで無料とありますが24時間×31日で744時間なので要は1年間ずっと無料ということです]
//footnote[cmanUrl3][@<href>{https://www.cman.jp/network/support/nslookup.html}]

== nslookupはもう卒業！digコマンドの便利な使い方

ドメイン名に紐づくIPアドレスを調べたいとき、あるいはIPアドレスに紐づくドメイン名を調べたいときはdigコマンド@<fn>{dig}を使用します。

//footnote[dig][digはdomain information groperの略です。ちなみにGoogleに翻訳してもらったら「ドメイン情報痴漢」でした。gropeは手さぐりするという意味なので、ドメイン情報を手探りして調べてきてくれるということです。余談ですがpingのgも同じgroperなのでdigが痴漢ならpingも痴漢です]

たとえば本著（改訂第2版）を頒布する技術書典7のウェブサイトは@<href>{https://techbookfest.org/event/tbf07}というURLです。このサイトがどこのウェブサーバに乗っているのか知りたかったらdigコマンドで引数に「techbookfest.org」というドメイン名を渡してやれば調べられます。早速digを叩いてみましょう。

//cmd{
$ dig techbookfest.org

; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.68.rc1.el6_10.3 <<>> techbookfest.org
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 54916
;; flags: qr rd ra; QUERY: 1, ANSWER: 4, AUTHORITY: 4, ADDITIONAL: 8

;; QUESTION SECTION:
;techbookfest.org.              IN      A

;; ANSWER SECTION:
techbookfest.org.       300     IN      A       216.239.38.21
techbookfest.org.       300     IN      A       216.239.32.21
techbookfest.org.       300     IN      A       216.239.34.21
techbookfest.org.       300     IN      A       216.239.36.21

;; AUTHORITY SECTION:
techbookfest.org.       86400   IN      NS      ns-cloud-b4.googledomains.com.
techbookfest.org.       86400   IN      NS      ns-cloud-b3.googledomains.com.
techbookfest.org.       86400   IN      NS      ns-cloud-b2.googledomains.com.
techbookfest.org.       86400   IN      NS      ns-cloud-b1.googledomains.com.

;; ADDITIONAL SECTION:
ns-cloud-b1.googledomains.com. 345600 IN A      216.239.32.107
ns-cloud-b1.googledomains.com. 345600 IN AAAA   2001:4860:4802:32::6b
ns-cloud-b2.googledomains.com. 345600 IN A      216.239.34.107
ns-cloud-b2.googledomains.com. 345600 IN AAAA   2001:4860:4802:34::6b
ns-cloud-b3.googledomains.com. 345600 IN A      216.239.36.107
ns-cloud-b3.googledomains.com. 345600 IN AAAA   2001:4860:4802:36::6b
ns-cloud-b4.googledomains.com. 345600 IN A      216.239.38.107
ns-cloud-b4.googledomains.com. 345600 IN AAAA   2001:4860:4802:38::6b

;; Query time: 260 msec
;; SERVER: 127.0.0.1#53(127.0.0.1)
;; WHEN: Thu Aug 29 20:22:39 2019
;; MSG SIZE  rcvd: 395
//}

ただtechbookfest.orgに紐づくIPアドレスが知りたかっただけなのに、ものすごくいっぱい出てきました。

digはまるでブキチ@<fn>{bukichi}のようなコマンドなのでちょっと聞いただけで「調べてきた結果を教えまし！まずキミの質問はこれでし！このドメイン名に紐づくIPアドレスはこれとこれとこれとこれなのでし！ちなみにIPアドレスを教えてくれたネームサーバの名前はこれでし、ネームサーバのIPアドレスはこっちなのでし！それからフルリゾルバは127.0.0.1で調査には260msecかかったのでし！」と調査の過程や付加情報まで含めて全部教えてくれます。

//footnote[bukichi][スプラトゥーン2に出てくる武器屋の店主。ブキの話になると超早口で果てしなく解説するブキマニア。語尾が「でし！」でオタク感があふれていて素晴らしく可愛い]

有難いのですが情報は多くありすぎても混乱します。「いいから簡潔にtechbookfest.orgに紐づくIPアドレスだけを教えて！」という場合は+shortというオプションを付けましょう。+shortさえつければdigはごく簡潔に答えてくれます。

//cmd{
$ dig techbookfest.org +short
216.239.34.21
216.239.36.21
216.239.38.21
216.239.32.21
//}

=== hostやnslookupじゃダメですか？

ちなみにhostコマンドやnslookupコマンドでも同じように調べることができます。

//cmd{
$ host -t a techbookfest.org
techbookfest.org has address 216.239.36.21
techbookfest.org has address 216.239.38.21
techbookfest.org has address 216.239.32.21
techbookfest.org has address 216.239.34.21
//}

//cmd{
$ nslookup
> set type=a
> techbookfest.org
Server:         172.31.0.2
Address:        172.31.0.2#53

Non-authoritative answer:
Name:   techbookfest.org
Address: 216.239.36.21
Name:   techbookfest.org
Address: 216.239.38.21
Name:   techbookfest.org
Address: 216.239.32.21
Name:   techbookfest.org
Address: 216.239.34.21
> exit
//}

大昔はnslookupを叩くと「nslookupは非推奨だし、将来的には廃止されるから今後はdigやhostを使ってね@<fn>{nslookupIsDeprecated}」という警告メッセージが都度出ていたので、その頃を知っている人は「nslookupっていずれなくなるんでしょ？」という認識かと思いますが、実際はBIND@<fn>{bind}9.9.0a3が公開されたタイミングでnslookupからこの警告メッセージは消え、リリースノートには「nslookupを非推奨として扱うのはもうやめるね。非推奨の警告も消したよ@<fn>{noLongerDeprecated}」と書かれていますので、nslookupが非推奨だの廃止だのという話は一旦なくなったようです。

//footnote[nslookupIsDeprecated][Note: nslookup is deprecated and may be removed from future releases. Consider using the `dig' or `host' programs instead.と表示されていました]
//footnote[bind][BINDはフルリゾルバとネームサーバ両方の機能を持つDNSサーバで、ISC（Internet Software Consortium）によって開発が行われています。多くのDNSサーバでBINDが採用されていますが「夏のBIND脆弱性祭り」などと揶揄されるほど脆弱性の注意喚起とそれに伴うアップデート推奨が多いため、最近はUnboundなど他のDNSサーバへの乗り換えもよく聞かれます]
//footnote[noLongerDeprecated][nslookup is no longer to be treated as deprecated. Remove "deprecated" warning message.]

実際、何もトラブルが起きておらず、単純に名前解決した結果を知りたいだけであればhostやnslookupでも事足ります。ですがトラブル発生時の調査手段としてhostやnslookupを使おうとすると、必要な情報が不足していたり調べてきた結果を下手に加工して出力したりするため、どちらもあまり使いやすいコマンドとは言えません。これを機に今後はdigを使っていきましょう！

== Whoisを叩いてドメイン名やIPの持ち主を調べよう

whoisコマンドを使うと、@<chapref>{domain}でお話ししたようなWhois情報を調べることができます。しかもwhoisコマンドはドメイン名の持ち主だけでなく、IPアドレスの持ち主を調べることもできます。

//cmd{
ドメイン名の持ち主を調べる
$ whois ドメイン名

IPアドレスの持ち主を調べる
$ whois IPアドレス
//}

=== 【ドリル】ドメイン名の有効期限が分からない

==== 問題

あなたはかき氷を作れるきょろちゃん@<fn>{kyoro}のサイト運用担当者です。（@<img>{kyoro}）

//image[kyoro][きょろちゃん][scale=0.8]{
//}

このたび運用担当を新人へ引き継ぐことになりました。引継ぎ資料を読んだ新人から「ここに毎年ドメイン名の更新作業が必要って書いてあるんですけど、次の更新っていつごろですか？」と聞かれました。ドメイン名の有効期限を知るにはどのコマンドを叩けばいいですか？

//footnote[kyoro][@<href>{http://tigerkyoro.jp/}]

 * A. dig tigerkyoro.jp +short
 * B. whois tigerkyoro.jp

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はBです。whoisコマンドを叩くと「Expires on」や「Registry Expiry Date」といった項目に有効期限が表示されます。今回のtigerkyoro.jpであれば、次のようにwhoisコマンドを叩けば、ドメイン名の有効期限が2020/01/31であることが分かります。

//cmd{
$ whois tigerkyoro.jp
[Querying whois.jprs.jp]
[whois.jprs.jp]
[ JPRS database provides information on network administration. Its use is    ]
[ restricted to network administration purposes. For further information,     ]
[ use 'whois -h whois.jprs.jp help'. To suppress Japanese output, add'/e'     ]
[ at the end of command, e.g. 'whois -h whois.jprs.jp xxx/e'.                 ]

Domain Information:
[Domain Name]                   TIGERKYORO.JP

[Registrant]                    Tiger Corporation

[Name Server]                   ns.namedserver.net
[Name Server]                   ns2.namedserver.net
[Signing Key]                   

[Created on]                    2016/01/18
[Expires on]                    2020/01/31
[Status]                        Active
[Last Updated]                  2019/02/01 01:17:18 (JST)

Contact Information:
[Name]                          Clarivate Analytics (Japan) Co.,Ltd.
[Email]                         domain.jp@markmonitor.com
[Web Page]                       
[Postal code]                   107-6119
[Postal Address]                Akasaka Park Building, 19F,
                                5-2-20, Akasaka,Minato-ku,Tokyo
[Phone]                         03-4589-3900
[Fax]                           03-4589-3240
//}

但しjpドメイン名の場合、たとえば2019年末の時点で新人が更新費用を支払って更新の手続きを済ませたとしても、Whoisの「Expires on」の表示が変わるのは、いま表示されている有効期限（2020/01/31）の翌月1日（2020/02/01）になってからです。@<fn>{expiresOn}comやnetなどのドメイン名であれば、更新手続きを完了するとWhoisの有効期限の表示もすぐに更新されます。

//footnote[expiresOn][JPドメインの更新費用を支払ったのですが　有効期限が更新されていません。 – さくらのサポート情報 @<href>{https://help.sakura.ad.jp/hc/ja/articles/206057382-JP%E3%83%89%E3%83%A1%E3%82%A4%E3%83%B3%E3%81%AE%E6%9B%B4%E6%96%B0%E8%B2%BB%E7%94%A8%E3%82%92%E6%94%AF%E6%89%95%E3%81%A3%E3%81%9F%E3%81%AE%E3%81%A7%E3%81%99%E3%81%8C-%E6%9C%89%E5%8A%B9%E6%9C%9F%E9%99%90%E3%81%8C%E6%9B%B4%E6%96%B0%E3%81%95%E3%82%8C%E3%81%A6%E3%81%84%E3%81%BE%E3%81%9B%E3%82%93-}]

== digを叩いてリソースレコードを確認してみよう

ここからは調べたい内容に応じて、どうdigコマンドを叩けばいいのか？を1つ1つ確認していきます。digを叩いてもサーバは壊れないし、地球も爆発しません。軽い気持ちでどんどん叩いてdigに慣れていきましょう。

=== Aレコード

たとえば「www.example.jpは203.0.113.222」や「mx.example.comは203.0.113.22」のように、ドメイン名とIPアドレスを紐づけているのがAレコードです。あなたが「このサイトはどこにあるんだろう？」と思ったら、次のようにdigコマンドを叩いてみましょう。@<fn>{prompt}するとそのドメイン名に紐づくIPアドレスが表示されるはずです。

//cmd{
$ dig ドメイン名 a +short
//}

//footnote[prompt][一番左の「$」はサーバにログインしたときにユーザ名やサーバの名前が表示される「プロンプト」というものを表しています。この「$」は実際は入力しなくていいので、dig以降を入力してください]

=== 【ドリル】ウェブサーバはどこにある？

==== 問題

あなたはCIAOちゅ〜るの「ちゅ〜るメーカー」というサイト（@<href>{https://www.inaba-petfood.co.jp/ciao-chuuuuuuuuuuru/}）の運用担当になりました。@<fn>{exampleSite}（@<img>{chiaoChuru}）

ところが前任者が急に辞めてしまって引継ぎ資料も見当たらず、このサイトがどこのウェブサーバで動いているのかちっとも分かりません。

//footnote[exampleSite][もちろん例えです。本著及び筆者は「ちゅ〜るメーカー」をはじめ、例題に使用させていただいたサイトと何の関係もありません。「ちゅ～る」と聞くと目の色を変える猫を飼っているだけです]

//image[chiaoChuru][あなたのねこちゃんとちゅ〜るCMをつくろう！ | CIAOちゅ〜るメーカー][scale=0.8]{
//}

「ちゅ〜るメーカー」のウェブサーバはどこのサービスを使っているのでしょうか？

 * A. さくらインターネット
 * B. AWS
 * C. IDCFクラウド

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はAです。

先ず「dig ドメイン名 a +short」でドメイン名からIPを引いてみましょう。サイトのURLが@<href>{https://www.inaba-petfood.co.jp/ciao-chuuuuuuuuuuru/}なので、確認すべきドメイン名は@<code>{www.inaba-petfood.co.jp}です。

//cmd{
$ dig www.inaba-petfood.co.jp +short
133.242.53.94
//}

IPアドレスは分かりましたが、IPアドレスだけではまだどこのクラウドサービスなのか分かりません。さらにwhoisコマンドでこのIPアドレスの持ち主を調べてみましょう。@<fn>{twoIp}

@<code>{whois 133.242.53.94}を叩いてみると、Organizationに@<code>{SAKURA Internet Inc.}とありますので、このIPアドレスはさくらインターネットのものであることが分かります。これでCIAOちゅ〜るのサイトがさくらインターネットのサービス上で動いていることが分かりました。

//footnote[twoIp][この例ではdigコマンドで出てきたIPが1つだけでしたが、複数出てきた場合はどちらでも構いません]

//cmd{
$ whois 133.242.53.94
（中略）
Network Information:            
a. [Network Number]             133.242.53.0/24
b. [Network Name]               SAKURA-NET
g. [Organization]               SAKURA Internet Inc.
（後略）
//}

===[column] 【コラム】同じドメイン名でAレコードを複数作るとどうなる？

たとえばウェブサーバが2台あった場合、次のようにまったく同じドメイン名でIPアドレスが異なるAレコードを複数作ることができます。

//cmd{
www.example.com.  300  IN  A  203.0.113.111
www.example.com.  300  IN  A  203.0.113.222
//}

このようなAレコードを設定した状態で、digコマンドでwww.example.comのAレコードを問い合わせると、次のような応答が返ってきます。

//cmd{
$ dig www.example.com a +short
203.0.113.111
203.0.113.222

または

$ dig www.example.com a +short
203.0.113.222
203.0.113.111
//}

問い合わせるたびに応答される2つのIPアドレスの順番が変わって「203.0.113.111」が先になったり「203.0.113.222」が先になったりすることで、エンドユーザのアクセスを2つに割り振ることができます。これをDNSラウンドロビンと言います。ロードバランサーがなくてもこのようにDNSの設定だけで簡易な負荷分散@<fn>{balancing}ができます。

ちなみに同じドメイン名で複数のレコードを作る場合、次のようにレコードによって異なるTTLを設定することは非推奨となっています。@<fn>{rfc2181}

//cmd{
www.example.com.  300  IN  A  203.0.113.111
www.example.com.  600  IN  A  203.0.113.222
//}

お名前.comのネームサーバでこのようなレコードを作ろうとすると「ホスト名が同じ文字列のレコードを複数ご登録頂く場合は、異なるTTLは設定できません」と表示されて、そもそも設定できません。蛇足ですが筆者が個人で運用しているネームサーバ@<fn>{bindVersion}で前述のような異なるTTLを設定してみた上でdigで問い合わせてみたところ、次のようにTTLは300に揃えられた状態で応答が返ってきました。

//cmd{
www.example.com.  300  IN  A  203.0.113.111
www.example.com.  300  IN  A  203.0.113.222
//}

===[/column]

//footnote[balancing][但し応答で返ってきた複数のIPアドレスのうち、どのIPアドレスにアクセスするのかはクライアントの実装に依存します。もし片方のウェブサーバが落ちてしまっても、ロードバランサーのように自動で分散対象から外してくれる訳でもないので、あくまで擬似的な負荷分散と捉えた方がいいでしょう]
//footnote[rfc2181][@<href>{https://tools.ietf.org/html/rfc2181#section-5.2}]
//footnote[bindVersion][BIND 9.8.2]

=== MXレコード

「〇〇@example.co.jp」というメールアドレス宛てにメールを送ったらこのメールサーバで受信します、という設定をしているのがMXレコードです。「このメールアドレスってメールはどこで受信してるんだっけ？」と思ったら、次のようにdigコマンドを叩いてみましょう。

//cmd{
$ dig ドメイン名 mx +short
//}

たとえば任天堂の問い合わせ窓口であるinfo@nintendo.co.jpにメールを送ったら、どこのメールサーバが受信するのか確認してみましょう。

//cmd{
$ dig nintendo.co.jp mx +short
10 nintendo-co-jp.mail.protection.outlook.com.
//}

「nintendo-co-jp.mail.protection.outlook.com」というのがメール受信サーバであることが分かりました。先頭の10はプリファレンス値といって「メールサーバが複数台ある場合の優先度」を表しています。MXレコードは複数設定できるため、プリファレンス値が10のメールサーバを複数台用意して負荷を分散したり、プリファレンス値が10のメールサーバが落ちていたら代わりにプリファレンス値が20のメールサーバで受信する、というように冗長性を高めたりできます。

MXレコードから察するに任天堂はOffice 365@<fn>{office365}を使っているようです。さらに@<code>{nintendo-co-jp.mail.protection.outlook.com}のAレコードを引くと、最終的にはメール受信サーバのIPアドレスまでたどり着くことができます。

//footnote[office365][Microsoftの法人向けサービス。メールやグループウェア、Microsoft Officeなどを利用できる]

//cmd{
# dig nintendo-co-jp.mail.protection.outlook.com a +short
104.47.93.36
104.47.92.36
//}

==== MXレコードがなければ代わりにウェブサーバ宛てにメールが届く

ところで、もしMXレコードが存在しなかったらどうなるのでしょう？メールを送ろうとしたとき、そのドメイン名のMXレコードが存在しなかったらメールを送信できない…のではなく、代わりにAレコードで紐づけられているIPアドレスに対してメールを送ろうとします。@<fn>{rfc5321}

//footnote[rfc5321][@<href>{https://tools.ietf.org/html/rfc5321#section-5.1}]

つまり「今回は@<href>{https://example.co.jp/}というサイトを公開したいだけで、メールを送受信する要件はまったくないのでexample.co.jpのMXレコードは設定しません」と思っていても、@<code>{example.co.jp}のAレコードさえあれば、そこに書かれたウェブサーバに対してメールが飛んできてしまう可能性があるのです。さらにPostfix@<fn>{postfix}はCentOSを最小限の構成でインストールしたときでも入っているので、全然意図していなかったけれどうっかりウェブサーバでPostfixが動いていて、エンドユーザから送られてきた個人情報満載なメールをひっそり受信していた！という可能性もあります。

//footnote[postfix][メール転送エージェント。要はメールを受信したり送信したりするためのメールサーバ]

そのドメイン名でメールを受信する予定がないのであれば、次のようにプリファレンス値を「0（ゼロ）」、メールサーバ名を「.（ドット）」にしたNull MX@<fn>{nullMx}を設定することで「メールを受信しません」という意図を明示しておく方が、メールを送る側も受信する側にも余計な負担がなくなってよいかも知れません。

//footnote[nullMx][@<href>{https://tools.ietf.org/html/rfc7505}]
//cmd{
example.co.jp.    IN  MX    0  .
//}

ただし、メールを受信する要件がなかったとしても、メールを送信する要件がある場合はバウンスメール@<fn>{bounceMail}受信のためにMXレコードを設定しておくべきです。

//footnote[bounceMail][宛先のメールアドレスが間違っていた、などの理由でメールが正常に配信できなかった場合に送信元に対して戻ってくるメールのこと。MAILER-DAEMONやリターンメール、エラーメールとも呼ばれる]

=== 〈トラブル〉test@test.co.jpを使って情報漏洩

あなたは広告代理店B社のプロデューサーで、A社の新製品である花粉症用マスクの先行体験キャンペーンを企画・担当しています。

キャンペーンサイトのフォームから新製品の先行体験キャンペーンに申し込むと、お客様には「応募を受け付けました」というメールが届きます。このメールにはお客様がフォームで記入された住所や電話番号などが書いてあります。

この受付完了メールですが、実は送信元メールアドレス（From）を何にするのか、実装が始まった時点では仕様が決まっていませんでした。そのため送信元メールアドレスは、ディレクターが仕様書に取り合えずのつもりで書いておいた@<code>{info@test.co.jp}というアドレスで実装されてしまい、テストでも誰も気づかないまま本番リリースを迎えてしまいました。

キャンペーンが始まり、花粉症のCさんは早速フォームから申し込みました。しかしCさんは最近引っ越したばかりだったので、うっかり古い住所をフォームで送ってしまいました。「応募を受け付けました」メールを見て住所が間違っていることに気づいたCさんは、すぐにメールの返信で@<code>{info@test.co.jp}宛てに「入力した住所が間違っていました。正しい住所は〇〇なので訂正したいです」という問い合わせを送りました。

しかしいつまで経っても返事が来ません。Cさんがキャンペーン事務局にクレームの電話を入れてエンジニアのDさんが調査をした結果、送信元メールアドレスがA社ではなく@<code>{info@test.co.jp}になっていた問題が発覚しました。果たしてCさんが@<code>{info@test.co.jp}宛てに送ったメールはどこへ行ってしまったのでしょう？

プロデューサーのあなたもエンジニアのDさんと一緒にこの問題を調査してみましょう。メール受信サーバを知りたいときは@<code>{dig ドメイン名 mx +short}です。

//cmd{
$ dig test.co.jp mx +short
10 mail10.heteml.jp.
//}

Cさんが@<code>{info@test.co.jp}宛てに送ったメールを受信しているのは@<code>{mail10.heteml.jp}であることが分かりました。@<code>{mail10.heteml.jp}についてウェブで検索してみたところ、どうやらGMOペパボがやっているヘテムル@<fn>{heteml}というクラウドサービスのメールサーバのようです。

//footnote[heteml][@<href>{https://heteml.jp/}]

@<code>{〇〇@test.co.jp}に送ったメールはヘテムルで受信している、というところまで分かりましたが、そもそも@<code>{test.co.jp}というドメイン名は誰の持ち物なのでしょうか？今度はwhoisでドメイン名の持ち主を調べてみましょう。

//cmd{
$ whois test.co.jp
[Querying whois.jprs.jp]
[whois.jprs.jp]
[ JPRS database provides information on network administration. Its use is    ]
[ restricted to network administration purposes. For further information,     ]
[ use 'whois -h whois.jprs.jp help'. To suppress Japanese output, add'/e'     ]
[ at the end of command, e.g. 'whois -h whois.jprs.jp xxx/e'.                 ]

Domain Information:
a. [Domain Name]                TEST.CO.JP
g. [Organization]               EDUCATIONAL ASSESSMENT INSTITUTE LIMITED COMPANY
l. [Organization Type]          Limited Company
m. [Administrative Contact]     TY2813JP
n. [Technical Contact]          KT071JP
p. [Name Server]                dns0.heteml.jp
p. [Name Server]                dns1.heteml.jp
s. [Signing Key]                
[State]                         Connected (2020/02/29)
[Registered Date]               2000/02/14
[Connected Date]                2000/02/16
[Last Update]                   2019/03/01 01:04:30 (JST)
//}

Whoisで調べてみると、このように@<code>{test.co.jp}というドメイン名は「EDUCATIONAL ASSESSMENT INSTITUTE LIMITED COMPANY」という名前の有限会社の持ち物である、という情報が出てきました。プロデューサーのあなたとエンジニアのDさんはなんだか嫌な予感がして、ブラウザで@<href>{http://test.co.jp/}（@<img>{testCoJp}）を開いてみました。すると有限会社教育評価研究所という会社のウェブサイトが表示されました。

//image[testCoJp][教育評価研究所][scale=0.8]{
//}

なんと花粉症のCさんが@<code>{info@test.co.jp}宛てに送ったお問い合わせメールは、クライアントのA社とも広告代理店のB社とも何の関係もない有限会社教育評価研究所という会社に飛んでしまったようです。「エンドユーザの個人情報漏洩だ、やってしまった…」とあなたとDさんは頭を抱えました。

==== 自分のものでないドメイン名を使うべきでない理由

このように「自分の持ち物でないドメイン名」を勝手に使うのはトラブルの元です。

 * test.co.jp
 * test.com
 * aaa.com
 * xxx.com

などはいかにもサンプルっぽいので、なんとなく「田中一郎」や「山田太郎」のようなノリで使いたくなってしまいますが、これらのドメイン名にはいずれもちゃんと持ち主@<fn>{exampleDomain}がいます。

//footnote[exampleDomain][たとえばtest.comというドメイン名はDOSarrestというサービスをやっている Internet Security LTD,という会社が持ち主ですし、前述のとおりtest.co.jpというドメイン名は有限会社教育評価研究所という会社が持ち主です]

そのためたとえば宅配ピザのステージングサイトで、仮に@<code>{tanaka@test.co.jp}というメールアドレスのテストユーザを作ってテストを行うと、実際に有限会社教育評価研究所という会社に会員登録完了メールや注文完了メールが飛んでいってしまい、相手方にご迷惑であると共に情報漏洩の恐れもあります。なかなかぴんと来ないかも知れませんが、誰かがアンケートに適当な住所を書いたせいで全然関係ない自分の家にダイレクトメールが届いたら迷惑ですよね。

ありがちですがお問い合わせフォームのメールアドレスの例に@<code>{sample@test.com}のように書くのもやめましょう。銀行に行って申請用紙のサンプルに自分の住所が部屋番号までばっちり書かれていたらぎょっとしますよね？それと同じことです。実在する他人の住所や電話番号を勝手に使わないのと同じように、他人のドメイン名も勝手に使わないようにしましょう。

==== 例示やテスト専用のドメイン名を使おう

他人が持っているドメイン名を勝手に使ってはいけない、ということは分かりました。では誰のものでないドメイン名ならいいのでは？と思われるかも知れませんが、現時点で誰のものでもなくても明日には誰かがそのドメイン名を登録するかも知れませんのでこれもやはりお勧めしません。

じゃあどうしたらいいのかというと、実はインターネットでは「例示やテストで使っていいドメイン名」というものが定められて@<fn>{rfc2606}います。テストユーザのメールアドレスや、フォームで例として書くメールアドレスには次のドメイン名を使いましょう。

 * example.co.jp
 * example.jp
 * example.com
 * example.net

//footnote[rfc2606][RFC2606で定められているexample.comやexample.net、もしくはJPRSが定めているexample.jpやexample.co.jpなどを使いましょう。@<href>{https://jprs.jp/faq/use/}]

これらのドメイン名であれば将来的に誰かのものになる可能性もありませんし、予期せぬ第三者へうっかりメールが飛んでいってしまうことも避けられます。

===[column] 【コラム】digのオプションは略せる

digコマンドには「+short」や「+norecurse」のようなクエリオプションがありますが、それぞれ後ろの何文字かを省略して「+shor」や「+norec」でも実行可能です。

このような「コマンドオプションって略せるの？！」といったdigの細かい仕様や仕組みをもっと詳しく知りたい！という方は、JPRSが公開している「初心者のためのDNS運用入門 - トラブル事例とその解決のポイント -」@<fn>{dnsBeginner}という資料がお勧めです。

===[/column]

//footnote[dnsBeginner][@<href>{https://dnsops.jp/event/20140626/dns-beginners-guide2014-mizuno.pdf}]

=== NSレコード

ドメイン名のネームサーバを指定しているのがNSレコードです。キャンペーンサイト用にサブドメインを増やしたいけど、サブドメインってどこで作ればいいんだっけ？というときは次のようなdigコマンドを叩いてNSレコードを調べれば分かります。

//cmd{
$ dig ドメイン名 ns +short
//}

=== 【ドリル】他社へのサイト移管時にネームサーバの所在が不明

==== 問題

あなたはWeb制作会社A社でボタニカルシャンプーのサイト（@<href>{https://herbgarden-sf.com/}）の運用を担当しているエンジニアです。（@<img>{herbGarden}）

//image[herbGarden][ボタニカルシャンプーのサイト][scale=0.8]{
//}

このたびクライアントの意向でサイトの運用をA社からライバルのB社へ移管することになりました。クライアント経由でB社から「DNSも弊社管理のネームサーバに移管するので現状のゾーン情報をください」と言われたのですが、インフラに関する資料がなくてネームサーバがどこにあるのか分かりません。このドメインのネームサーバはどこにあるのでしょうか？

 * A. AWSのRoute53
 * B. MicrosoftのAzure DNS
 * C. IDCFクラウド DNS

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はAです。次のようにdigコマンドを叩くと「awsdns」という文字を含むネームサーバ名が返ってくるので、ネームサーバがAWSのRoute53であることが分かります。

//cmd{
$ dig herbgarden-sf.com ns +short
ns-1030.awsdns-00.org.
ns-910.awsdns-49.net.
ns-1805.awsdns-33.co.uk.
ns-418.awsdns-52.com.
//}

ゾーンの中のリソースレコードを確認するにはAWSのマネジメントコンソールにログインする必要がありますが、AWSアカウント名やパスワードまではさすがにdigでは分からないので、そこはなんとか過去資料から探してください。またRoute53にはホストゾーンのエクスポート機能がないので、リソースレコードを1つ1つコピーペーストするかCLI@<fn>{cli}を駆使して取得する必要があります。

//footnote[cli][コマンドラインインターフェイスの略。AWSはブラウザでぽちぽち操作するだけでなく、CLIを用いてコマンドラインからも操作できます]

=== SPFレコード（TXTレコード）

AさんがBさんに手紙を書くとき、封筒の差出人欄に「Cさんより」と書けば簡単に送信元を騙ることができます。メールもそれと同じで、送信元のメールアドレスを詐称して送信することは容易です。迷惑メールの多くはこのように送信元を詐称しているなりすましメールです。

このとき送り主が本物なのか、あるいは自分の持ち物でないドメイン名で送信元を詐称して勝手にメールを送っている「なりすましメール」なのかを確認する手段として、SPF@<fn>{spf}レコードというものがあります。SPFレコードは次のdigコマンドで確認できます。

//footnote[spf][Sender Policy Frameworkの略]

//cmd{
$ dig ドメイン名 txt +short
//}

SPFレコードなのにtxtなの？と疑問に思われるかも知れません。昔はSPFを設定する方法としてSPFレコードとTXTレコードという2種類のリソースレコードに書くことが推奨されていたのですが、SPFレコードに書く方法は普及せず、最終的に「SPFはTXTレコードで設定すること」となりました。@<fn>{rfc7208}

//footnote[rfc7208][@<href>{https://tools.ietf.org/html/rfc7208#section-3.1}でSPF records MUST be published as a DNS TXT (type 16) Resource Record(RR) [RFC1035\] onlyと書かれています]

たとえばポケモンだいすきクラブ@<fn>{pokemon}から届く「ポケモンだいすき！通信」というメールは、送信元のメールアドレスが@<code>{noreply@pdc.pokemon.jp}です。@<code>{pdc.pokemon.jp}のSPFレコードを確認してみましょう。

//footnote[pokemon][ポケモンの情報サイト。ミミッキュのうたは名曲です。@<href>{http://www.pokemon.jp/}]

//cmd{
$ dig pdc.pokemon.jp txt +short
"v=spf1 include:spf.pdc.pokemon.jp include:spf.pokemon.mailds.jp ~all"
"google-site-verification=Vg3Ar1_hRlrET3eyTiQS8ONtb_ijVAZh1ME3FaWX-Mw"
//}

@<code>{pdc.pokemon.jp}のTXTレコードは複数あるようですが、SPFレコードは1つめの@<code>{v=spf1}で始まる方です。includeは引数で渡しているドメイン名のSPFレコードを含むという意味ですので、さらに@<code>{spf.pdc.pokemon.jp}と@<code>{spf.pokemon.mailds.jp}のSPFレコードを引いてみましょう。

//cmd{
$ dig spf.pdc.pokemon.jp txt +short
"v=spf1 +ip4:203.216.217.0/24 +ip4:122.212.36.0/24 +ip4:202.8.80.0/23
 +ip4:202.74.4.160/27 +ip4:59.159.71.0/24 +ip4:220.110.139.188/32
 +ip4:211.120.127.41/32 +ip4:125.29.35.0/26 +ip4:124.211.29.64/26
 +ip4:122.215.202.64/26 +ip4:203.138.159.219 ~all"

$ dig spf.pokemon.mailds.jp txt +short
"v=spf1 ip4:118.238.144.96/29 ip4:118.238.144.120/30 ~all"
//}

最初の@<code>{+ip4:203.216.217.0/24}は「203.216.217.0～203.216.217.255のIPアドレスをメールの送信元サーバとして認める」という意味です。ひとつひとつ解説するには量が多すぎるので省略しますが、要はここに書いてあるIPアドレスから届いたメールは本物で、それ以外は恐らく迷惑メールだよ、ということを示しています。実際に届いた「ポケモンだいすき！通信」の送信元IPは「118.238.144.99」でしたので、きちんとSPFレコードの中に含まれており、それによってメールは迷惑メール扱いされることなく受信ボックスに届きました。

=== 【ドリル】どうしてメールが迷惑メール扱いされるの？

==== 問題

あなたはWeb制作会社A社のフロントエンドエンジニアです。小規模なクライアントB社からの依頼でキャンペーンサイト（@<href>{https://campaign.example.com/}）を構築したのですが、後から「問い合わせフォームが欲しい」という追加要望が出てきました。

予算もあまりないためフォームは実装せず、問い合わせのページだけは簡単にフォームが作れる外部のASPサービスを使うことにしました。エンドユーザがフォームから問い合わせを行うと、そのASPサービスがB社とエンドユーザの両方に「問い合わせを受け付けました」というメールを送ってくれます。このとき送信元のメールアドレスは@<code>{info@example.com}です。

ところがB社の担当者から「問い合わせ受付メールが迷惑メール扱いされて迷惑メールボックスに入ってしまう。エンドユーザの方でも同じ現象が起きているようだ」というクレームが入りました。原因を調査するにはどのdigコマンドを叩くべきでしょうか？

 * A. dig example.com spf +short
 * B. dig campaign.example.com txt +short
 * C. dig example.com txt +short

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はCです。送ったメールが迷惑メール扱いされてしまうときは@<code>{dig ドメイン名 txt +short}でSPFレコードを確認しましょう。SPFレコードには、そのドメイン名でのメール送信を許可されているサーバのリストが書かれています。

今回、問い合わせ受付メールが迷惑メール扱いされてしまったのは、メールを送っているサーバのIPアドレスをSPFレコードに追加し忘れたことが原因と思われます。ASPサービスにメール送信元のIPアドレスを確認して、SPFレコードに追記しましょう。

=== 〈トラブル〉SPFを設定したのに時々迷惑メールになる

Aさんは猫の譲渡会ボランティアしています。ある日、メンバーのBさんから「猫の様子をネットで公開したいからWordPressでサイトを作ってくれないか」と頼まれました。アクセス数はそう多くなさそうなので、さくらインターネットが提供している「さくらのVPS（仮想専用サーバー）@<fn>{sakura}」でいちばん安いプランを契約した上で、WordPressのセッティングをしてBさんに引き渡しました。WordPressが動いているサーバのIPアドレスは@<code>{203.0.113.222}で、サイトのURLは@<code>{https://cat.example.com/}です。

//footnote[sakura][@<href>{https://vps.sakura.ad.jp/}]

このときWordPressから管理者宛てに送られてくるメール（送信元のメールアドレスは@<code>{wordpress@cat.example.com}）が迷惑メール扱いされないよう、Aさんは次のようにSPFレコードを設定しておきました。

//cmd{
cat.example.com.    600    IN    TXT    "v=spf1 ip4:203.0.113.222 -all"
//}

しかし数日後、Bさんから「パスワードを忘れてしまって、WordPressの管理画面から新しいパスワードを発行しようとしたが、パスワードをリセットするためのメールが迷惑メールのトレイに入ってしまう」と相談されました。詳しく聞くと、毎回必ず迷惑メールになってしまうのではなく、何度か試みるとその時によって迷惑メールのトレイに入ったり受信トレイに届いたりするそうです。AさんがBさんのGmailで迷惑メールのトレイに入ってしまった方のメールを見せてもらったところ、確かに「Received-SPF: fail」となっていました。一方、きちんと受信トレイに届いた方のメールは「Received-SPF: pass」になっていました。

何も設定を変えていないのに、なぜ迷惑メール扱いされたりされなかったりするんだろう？と悩みながら、Aさんは2通のメールのヘッダをよく見てみました。すると、迷惑メールのトレイに入ってしまった方のメールは、送信元が「2001:0db8:0000:0000:0000:0000:0000:0022」になっていました。

さくらのVPSはIPv6に対応しているため、その時々によってメールの送信元がIPv4の「203.0.113.222」だったり、IPv6の「2001:0db8:0000:0000:0000:0000:0000:0022」だったりしていたのです。それなのにSPFレコードでは「203.0.113.222をメールの送信元サーバとして認める。それ以外は認めない」という設定になっていたため、IPv6で送られてきたときは迷惑メール扱いされてしまっていたのでした。

AさんがSPFレコードを次のように修正@<fn>{ipv6}すると、迷惑メールになったりならなかったりする事象は無事に解消しました。

//cmd{
cat.example.com.    600    IN    TXT
  "v=spf1 ip4:203.0.113.222 ip6:2001:0db8:0000:0000:0000:0000:0000:0022 -all"
//}

//footnote[ipv6][ちなみに「ip6:2001:0db8:0000:0000:0000:0000:0000:0022」の部分は省略して「ip6:2001:0db8::22」と書くことも可能ですが、ここでは分かりやすさを優先して省略せずに書いています]

=== PTRレコード

Aレコードは前述のとおりドメイン名からIPアドレスを正引きできるレコードです。対してIPアドレスからドメイン名を逆引きできるレコードのことをPTRレコード@<fn>{ptr}と呼びます。

//footnote[ptr][PoinTeR recordの略]

メールを受信するメールサーバによっては「メール送信元のIPアドレスがSPFレコードに登録されていること」だけでなく「メール送信元のIPアドレスからドメイン名の逆引きができること」という条件も満たさないと迷惑メールと判断することがあります。

PTRレコードは次のdigコマンドで確認できます。

//cmd{
$ dig -x IPアドレス +short
//}

なおAレコードやMXレコードやSPFレコードといったドメイン名のリソースレコードと、PTRレコードのようなIPアドレスのリソースレコードは設定依頼をする先が異なります。筆者は@<code>{startdns.fun}というドメイン名を持っており、ネームサーバはRoute53を使用しているので、@<code>{startdns.fun}のAレコードやMXレコード、SPFレコードはRoute53で設定ができます。

ですが、たとえばさくらインターネットのVPSで借りたサーバのIPアドレスが@<code>{203.0.113.222}だったとして、このIPアドレスのPTRレコードをRoute53で設定することはできません。このIPに対してPTRレコードを設定できるのは、IPアドレスの持ち主であるさくらインターネットの管理画面からとなります。

=== CNAMEレコード

ときどきドメイン名からIPアドレスを引こうとしてdigでAレコードを調べたのに、こんな風に別のドメイン名とIPアドレスが返ってくることがあります。

//cmd{
$ dig aibo.sony.jp a +short
cs1018.wpc.omicroncdn.net.
152.195.38.205
//}

なぜaiboのサイト@<fn>{aibo}のAレコードを調べると@<code>{cs1018.wpc.omicroncdn.net}という全然関係のなさそうなドメイン名が出てくるのでしょう？+shortオプションを外して、この結果に至るまでの過程を見てみましょう。

//footnote[aibo][@<href>{https://aibo.sony.jp/}]

//cmd{
$ dig aibo.sony.jp a

; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.68.rc1.el6_10.3 <<>> aibo.sony.jp a
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 4163
;; flags: qr rd ra; QUERY: 1, ANSWER: 2, AUTHORITY: 4, ADDITIONAL: 8

;; QUESTION SECTION:
;aibo.sony.jp.                  IN      A

;; ANSWER SECTION:
aibo.sony.jp.           270     IN      CNAME   cs1018.wpc.omicroncdn.net.
cs1018.wpc.omicroncdn.net. 3570 IN      A       152.195.38.205

;; AUTHORITY SECTION:
omicroncdn.net.         172770  IN      NS      ns1.omicroncdn.net.
omicroncdn.net.         172770  IN      NS      ns2.omicroncdn.net.
omicroncdn.net.         172770  IN      NS      ns4.omicroncdn.net.
omicroncdn.net.         172770  IN      NS      ns3.omicroncdn.net.

;; ADDITIONAL SECTION:
ns1.omicroncdn.net.     172770  IN      A       72.21.80.5
ns1.omicroncdn.net.     172770  IN      AAAA    2606:2800:1::5
ns2.omicroncdn.net.     172770  IN      A       72.21.80.6
ns2.omicroncdn.net.     172770  IN      AAAA    2606:2800:1::6
ns3.omicroncdn.net.     172770  IN      A       192.229.254.5
ns3.omicroncdn.net.     172770  IN      AAAA    2606:2800:e::5
ns4.omicroncdn.net.     172770  IN      A       192.229.254.6
ns4.omicroncdn.net.     172770  IN      AAAA    2606:2800:e::6

;; Query time: 0 msec
;; SERVER: 127.0.0.1#53(127.0.0.1)
;; WHEN: Fri Aug 30 00:03:49 2019
;; MSG SIZE  rcvd: 333
//}

ANSWER SECTIONを見てみましょう。@<code>{aibo.sony.jp}のCNAMEレコードに@<code>{cs1018.wpc.omicroncdn.net}が設定されており、さらに@<code>{cs1018.wpc.omicroncdn.net}のAレコードに@<code>{152.195.38.205}が設定されていることが分かります。このとき@<code>{aibo.sony.jp}をaliases（別名）、@<code>{cs1018.wpc.omicroncdn.net}をcanonical name（正式名）と呼びます。

フルリゾルバは@<code>{aibo.sony.jp}のAレコードを調べに行って、Aレコードの代わりにCNAMEレコードが見つかった場合、名前解決の対象を正式名である@<code>{cs1018.wpc.omicroncdn.net}に置き換えて引き続きAレコードを調べ、最終的に@<code>{cs1018.wpc.omicroncdn.net}のAレコードで設定されているIPアドレスを返してきます。

このようにCNAMEレコードが設定されているときは、Aレコードを問い合わせても結果としてCNAMEレコードと、その正式名のAレコードの両方が返ってきますが、CNAMEレコードだけを調べたいときは次のdigコマンドで確認できます。

//cmd{
$ dig ドメイン名 cname +short
//}

=== 【ドリル】CNAMEの調べ方と使いどころ

==== 問題

キドキド@<fn>{kidoKidUrl}のサイト（@<img>{kidokid}）のドメイン名、@<code>{kidokid.bornelund.co.jp}のCNAMEレコードを知りたい場合、どのdigコマンドを叩けばよいでしょうか？

//footnote[kidoKidUrl][@<href>{https://kidokid.bornelund.co.jp/}]

//image[kidokid][キドキド（KID-O-KID）のサイト][scale=0.8]{
//}

 * A. dig kidokid.bornelund.co.jp cname +short
 * B. dig kidokid.bornelund.co.jp a +short
 * C. dig kidokid.bornelund.co.jp txt +short
 * D. dig kidokid.bornelund.co.jp mx +short

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はAです。ただしBもCNAMEレコードとそのAレコードが返ってくるので、Bも正解で構いません。CNAMEレコードはCDN@<fn>{cdn}やロードバランサーを使うときによく利用されます。

//footnote[cdn][Contents Delivery Networkの略。アクセスしてきたエンドユーザに最も近いサーバからサイトのコンテンツを効率的に配信できる仕組みのこと。CDNを使うとエンドユーザからのアクセスが分散されるため、TVやYahoo!ニュース、LINEのプッシュ通知などで一気にアクセスが殺到してもサイトが落ちたり重くなったりしないで済みます]

//cmd{
$ dig kidokid.bornelund.co.jp cname +short
bornelund-ELB-1960389134.ap-northeast-1.elb.amazonaws.com.
//}

CDNを使う場合だけでなく、1台のウェブサーバに大量のサイトが相乗りしているような場合もCNAMEレコードを使うと便利です。たとえばウェブサーバにサイトA、サイトB、サイトC…と計100サイトが相乗りしていてそれぞれがAレコードを設定していた場合、ウェブサーバを引っ越すとなったら100件のAレコードを書き換えなければなりません。ですが、Aレコードを設定しているのはサイトAのみで、それ以外のサイトはCNAMEでサイトAのドメイン名を指定するという方法にしておけば、サーバ引っ越しに際して書き換えなければならないのはサイトAのAレコードだけとなります。

=== CNAMEと他のリソースレコードは共存できない

一見便利なCNAMEレコードですが使用する際は注意点があります。それは「@<b>{CNAMEレコードを設定したら、他のリソースレコードは設定できない}」ということです。

たとえば次のようなCNAMEレコードとMXレコードは共存ができません@<fn>{rfc1912}。

//footnote[rfc1912][A CNAME record is not allowed to coexist with any other data. @<href>{http://www.ietf.org/rfc/rfc1912.txt}]

//cmd{
campaign.example.com.   IN   CNAME    cdn.example.jp.
campaign.example.com.   IN   MX       mail.example.com.
//}

@<code>{campaign.example.com}のCNAMEレコードで@<code>{cdn.example.jp}を設定すると、AレコードだけでなくMXレコードもTXTレコードもNSレコードも、ありとあらゆるリソースレコードが@<code>{cdn.example.jp}を参照しに行ってしまいます。そのため2行目で@<code>{campaign.example.com}のMXレコードで@<code>{mail.example.com}を設定しても、そのMXレコードは名前解決に使われることなく無視されてしまうのか、あるいは使われるのか動作がまったく保証されません。

このような理由からRoute53をはじめとするネームサーバのサービスでは、CNAMEレコードを設定した場合は他のリソースレコードが設定できないようになっています。

また「ありとあらゆるレコード」にはCNAMEレコードも含まれるため、次のようにCNAMEレコードを複数設定することもできません。

//cmd{
campaign.example.com.   IN   CNAME    cdn1.example.jp.
campaign.example.com.   IN   CNAME    cdn2.example.jp.
//}

==== ZONE APEXはCNAMEを使えない

前述の「CNAMEレコードは他のリソースレコードと共存できない」という理由から、@<idx>{ZONE APEX}@<fn>{zoneApex}ではCNAMEを設定することができません。筆者がCDNを使いたいと思っても、次のようなCNAMEレコードは設定できないのです。

//footnote[zoneApex][startdns.funやexample.jpのようにwwwやstgといったサブドメインを含まないドメイン名のこと。レジストラやリセラで買ったいちばん短い表記のドメイン名のことをZONE APEXと呼びます。Apex DomainやNaked Domain、ホスト名なしドメインなどと呼ばれることもあります]

//cmd{
startdns.fun.   IN   CNAME    cdn.example.jp.
//}

なぜならばCNAMEレコードが他のリソースレコードと共存できないのに対して、ZONE APEXには「このドメイン名はこのネームサーバを使うよ」というNSレコード、および「このドメイン名の管理情報はこれだよ」というSOAレコードが必ず存在するからです。（お名前.comで自分のドメイン名を買った後、Route53でホストゾーンを作成したらSOAレコードとNSレコードが自動生成されていたのを覚えていますか？）

==== Route53のAliasレコードならZONE APEXでも設定可能

前述の「CNAMEレコードは他のリソースレコードと共存できない」「ZONE APEXにはNSレコードとSOAレコードが必ず存在する」という2つの制限から、たとえCDNやELB@<fn>{elb}を使いたいと思ってもZONE APEXでは使用できなかったのですが、なんとRoute53のAliasレコードという独自拡張を使うとZONE APEXでもCDNを使うことができるのです。@<fn>{alias}

//footnote[elb][Elastic Load Balancingの略。AWSのサービスの1つでいわゆるロードバランサーのことです]
//footnote[alias][Route53のAliasの他にCloudFlareのCNAME Flatteningなど類似のサービスはいくつかあります]

しかもAliasレコードには「ZONE APEXでも使える」だけでなく、「CNAMEと違って名前解決が1回で済む」という利点があります。

たとえばstartdns.funというドメイン名に紐づくIPアドレスを調べようとしたとき、CNAMEレコードの場合は「startdns.funのCNAMEレコードはcdn.example.jpで、cdn.example.jpのAレコードは203.0.113.222」のように名前解決が2回発生します。対してRoute53のAliasレコードで「startdns.funのエイリアス先はcdn.example.jpである」という設定をしておけば、フルリゾルバがstartdns.funのAレコードを問い合わせに来たら「startdns.funのAレコードは203.0.113.222」のように一発でIPアドレスを返すので名前解決は1回で済みます。

ネームサーバでRoute53を使っていても、参照先のCDNやロードバランサーがAWS外なのであればCNAMEを使うしかありませんが、参照先がAWS内のサービスであればAliasレコードを使わない手はありません。ZONE APEXに限らず積極的に使いましょう。

=== グルーレコード

ところでドメイン名を買ったとき、お名前.comのネームサーバやRoute53を使う他に自力でネームサーバを立てて使うこともできます。Linuxサーバを立ててApacheをインストールすればウェブサーバになるように、Linuxサーバを立ててBINDをインストールすればもうそれは立派なネームサーバです。

たとえば筆者がstartdns.funというドメイン名を買って、自分で作ったネームサーバにns1.startdns.funという名前を付け、startdns.funのNSレコードにns1.startdns.funを設定したとします。このとき、ブラウザで@<href>{http://startdns.fun/}を開こうとすると次のようになります。

 1. フルリゾルバにstartdns.funに紐づくIPアドレスを聞きに行く
 1. フルリゾルバは自分の中にstartdns.funに紐づくIPアドレスのキャッシュがないことを確認
 1. フルリゾルバはルートネームサーバにstartdns.funに紐づくIPアドレスを聞きに行く
 1. ルートネームサーバは「.funのネームサーバはa.nic.funだよ」と教えてくれる
 1. フルリゾルバはa.nic.funにstartdns.funに紐づくIPアドレスを聞きに行く
 1. a.nic.funは「startdns.funのネームサーバはns1.startdns.funだよ」と教えてくれる
 1. フルリゾルバはルートネームサーバにns1.startdns.funに紐づくIPアドレスを聞きに行く
 1. ルートネームサーバは「.funのネームサーバはa.nic.funだよ」と教えてくれる
 1. フルリゾルバはa.nic.funにns1.startdns.funに紐づくIPアドレスを聞きに行く
 1. a.nic.funは「startdns.funのネームサーバはns1.startdns.funだよ」と教えてくれる
 1. ns1.startdns.funのIPアドレスを知っているのがns1.startdns.funなのでフルリゾルバはいつまでもns1.startdns.funにたどり着けない

「田中さんの住所は田中さんの家に行って田中さんに聞いて」みたいなもので、このままだといつまでもstartdns.funに紐づくIPアドレスが分かりません。

これを解消するため、自分でネームサーバを立てるときは上位のネームサーバ（ここではa.nic.funのこと）に、ネームサーバのIPアドレスも一緒に登録しておかなければいけません。これを@<b>{グルーレコード}と呼びます。上位のa.nic.funからns1.startdns.funへの道をちゃんと繋げてくれるレコードだからglue（接着剤のこと）レコードなんですね。

お名前.comであればドメインNaviの中に「ネームサーバー名としてのホストを設定する」という設定画面がありますので、そこで自分が立てたネームサーバのドメイン名（ns1.startdns.fun）とそのIPアドレス（203.0.113.222）を登録すればOKです。これでいつまでもns1.startdns.funにたどり着けない無限ループが回避できるようになります。

===[column] 【コラム】このIPアドレスはグローバルIP？プライベートIP？

ところでdigコマンドを叩いて「203.0.113.222」という応答が返ってきたとき、このIPアドレスがグローバルIPアドレス@<fn>{globalIp}なのか、プライベートIPアドレス@<fn>{privateIp}なのか、ぱっと見て判別できますか？

グローバルIPは「03-○○○○-○○○○」のような外線番号で、プライベートIPは「法務部の片岡さんは4322で、総務部の茂木さんは2652」のような内線番号だと思ってください。A社からB社に電話をかけるときは外線番号でないと繋がりませんが、A社のオフィス内で片岡さんが茂木さんにかけるときは内線番号を押せば繋がります。これと同じように、インターネットを介して通信するときはグローバルIPを使いますが、オフィスのように同じネットワーク内であればプライベートIPで通信ができます。

そして全世界のどこを探しても同じ電話番号を使っている人がいないのと同じように、インターネット上でグローバルIPは一意です。対してプライベートIPは同一ネットワーク内でのみ一意です。A社で法務部の片岡さんが内線番号4322を使っているときに、まったく別の会社で4322という内線番号を使っていても何の問題もないですよね。

そして実はプライベートIPアドレスの範囲はRFC1918@<fn>{rfc1918}で次のように定められています。

 * 10.0.0.0/8（10.0.0.0～10.255.255.255）
 * 172.16.0.0/12（172.16.0.0～172.31.255.255）
 * 192.168.0.0/16（192.168.0.0～192.168.255.255）

ですので、digコマンドを叩いてIPアドレスが返ってきた場合、ぱっと見てこの範囲外であれば「これはグローバルIPだな！」と判断できます。203.0.113.222もプライベートIPアドレスの範囲に含まれないのでグローバルIPですね。

===[/column]

//footnote[globalIp][グローバルIPはAWS上だとパブリックIPという名前で呼ばれています]
//footnote[privateIp][プライベートIPはローカルIPと呼ばれることもあります]
//footnote[rfc1918][@<href>{https://tools.ietf.org/html/rfc1918#section-3}]
