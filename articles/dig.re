=  digとwhoisを叩いて学ぶDNS

性能向上のための格言に「推測するな計測せよ」というものがありますが、障害発生時にも同じことが言えます。DNS絡みのトラブルが起きたとき、あるいはサイトが意図した動作をしないとき、調べ方さえ知っていれば原因を調査できますし「恐らくDNSの浸透が原因じゃないかと・・・48時間ほど待てば多分・・・」のようなエンジニアらしからぬ回答をしなくて済みます。

この章ではdigコマンドとwhoisコマンドを実際に叩いて色んなことを調べながら、DNSの仕組みを学んでいきましょう。

//pagebreak

== digとwhoisのインストール

digコマンドやwhoisコマンドを使いたくても、そこにインストールされていなければ使えません。Macにはどちらのコマンドも元々インストールされているので、あなたがMacユーザであればターミナルを起動すればすぐに使うことができます。

CentOSやAmazonLinuxなどのサーバ環境がある人は、そこでrootになって次のyumコマンドを叩けばインストールできます。

//cmd{
digコマンドのインストール
# @<b>{yum -y install bind-utils}

whoisコマンドのインストール
# @<b>{yum install -y jwhois}
//}

=== MacもLinuxのサーバ環境もない場合

パソコンはWindowsだしコマンドを叩けるような環境はない・・・という方は、Route53を使うために折角AWSでアカウントを作ったので、EC2@<fn>{ec2}でインスタンス@<fn>{instance}を立ててみるのがお勧めです。サーバスペックごとにインスタンスタイプという区分があるのですが、t2.microというインスタンスタイプならアカウント作成から1年間は毎月750時間まで無料で使えます。ここでは詳しく説明しませんが、AWSのマネジメントコンソールでEC2ダッシュボードを開いて「インスタンスの作成」を押したら、後は画面の表示に従ってぽちぽち選んでいくだけで5分もあればすぐにサーバが作れます。@<fn>{750h}

インスタンス立てるのはちょっと無理！という場合は、@<chapref>{aws}で使った「nslookup(dig)テスト【DNSサーバ接続確認】」@<fn>{cmanUrl3}というページや各レジストリのWhois情報確認サイトで疑似的にdigやwhoisを叩く形で代用しても構いません。

//footnote[ec2][Elastic Compute Cloudの略。AWSにはいろいろなサービスがありますがEC2はいわゆるサーバのことです。]
//footnote[instance][AWSではサーバのことをインスタンスを呼びます。]
//footnote[750h][月に750時間まで無料とありますが24時間×31日で744時間なので要は1年間ずっと無料ということです。]
//footnote[cmanUrl3][@<href>{https://www.cman.jp/network/support/nslookup.html}]

== nslookupはもう卒業！digコマンドの便利な使い方

ドメインに紐づくIPアドレスを調べたいとき、あるいはIPアドレスに紐づくドメインを調べたいときはdigコマンド@<fn>{dig}を使用します。

//footnote[dig][digはdomain information groperの略です。ちなみにGoogleに翻訳してもらったら「ドメイン情報痴漢」でした。gropeは手さぐりするという意味なので、ドメイン情報を手探りして調べてきてくれるということです。余談ですがpingのgも同じgroperなのでdigが痴漢ならpingも痴漢です。]

たとえば本著を初めて頒布する技術書典4のウェブサイトは@<href>{https://techbookfest.org/event/tbf04}というURLです。このサイトがどこのウェブサーバに乗っているのか知りたかったらdigコマンドで引数に「techbookfest.org」というドメインを渡してやれば調べられます。早速digを叩いてみましょう。

//cmd{
$ @<b>{dig techbookfest.org}

; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.62.rc1.el6_9.5 <<>> techbookfest.org a
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 48654
;; flags: qr rd ra; QUERY: 1, ANSWER: 4, AUTHORITY: 4, ADDITIONAL: 8

@<b>{;; QUESTION SECTION:}
;techbookfest.org.              IN      A

@<b>{;; ANSWER SECTION:}
techbookfest.org.       300     IN      A       216.239.32.21
techbookfest.org.       300     IN      A       216.239.34.21
techbookfest.org.       300     IN      A       216.239.36.21
techbookfest.org.       300     IN      A       216.239.38.21

@<b>{;; AUTHORITY SECTION:}
techbookfest.org.       75009   IN      NS      ns-cloud-b1.googledomains.com.
techbookfest.org.       75009   IN      NS      ns-cloud-b4.googledomains.com.
techbookfest.org.       75009   IN      NS      ns-cloud-b2.googledomains.com.
techbookfest.org.       75009   IN      NS      ns-cloud-b3.googledomains.com.

@<b>{;; ADDITIONAL SECTION:}
ns-cloud-b1.googledomains.com. 334209 IN A      216.239.32.107
ns-cloud-b1.googledomains.com. 334209 IN AAAA   2001:4860:4802:32::6b
ns-cloud-b2.googledomains.com. 334209 IN A      216.239.34.107
ns-cloud-b2.googledomains.com. 334209 IN AAAA   2001:4860:4802:34::6b
ns-cloud-b3.googledomains.com. 334209 IN A      216.239.36.107
ns-cloud-b3.googledomains.com. 334209 IN AAAA   2001:4860:4802:36::6b
ns-cloud-b4.googledomains.com. 334209 IN A      216.239.38.107
ns-cloud-b4.googledomains.com. 334209 IN AAAA   2001:4860:4802:38::6b

;; Query time: 148 msec
;; SERVER: 127.0.0.1#53(127.0.0.1)
;; WHEN: Sun Mar 11 11:51:13 2018
;; MSG SIZE  rcvd: 395
//}

ただtechbookfest.orgに紐づくIPアドレスが知りたかっただけなのに、ものすごくいっぱい出てきました。

digはまるでブキチ@<fn>{bukichi}のようなコマンドなのでちょっと聞いただけで「調べてきた結果を教えまし！まずキミの質問はこれでし！このドメインに紐づくIPアドレスはこれとこれとこれとこれなのでし！ちなみにIPアドレスを教えてくれたネームサーバの名前はこれでし、ネームサーバのIPアドレスはこっちなのでし！それからフルリゾルバは127.0.0.1で調査には148msecかかったのでし！」と調査の過程や付加情報まで含めて全部教えてくれます。

//footnote[bukichi][スプラトゥーン2に出てくる武器屋の店主。ブキの話になると超早口で果てしなく解説するブキマニア。語尾が「でし！」でオタク感があふれていて素晴らしく可愛い。]

有難いのですが情報は多くありすぎても混乱します。いいから簡潔に「techbookfest.orgに紐づくIPアドレス」だけを教えて！という場合は+shortというオプションを付けましょう。+shortさえつければdigはごく簡潔に答えてくれます。

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

//footnote[nslookupIsDeprecated][Note: nslookup is deprecated and may be removed from future releases. Consider using the `dig' or `host' programs instead.と表示されていました。]
//footnote[bind][BINDはフルリゾルバとネームサーバ両方の機能を持つDNSサーバで、ISC（Internet Software Consortium）によって開発が行われています。多くのDNSサーバでBINDが採用されていますが「夏のBIND脆弱性祭り」などと揶揄されるほど脆弱性の注意喚起とそれに伴うアップデート推奨が多いため、最近はUnboundなど他のDNSサーバへの乗り換えもよく聞かれます。]
//footnote[noLongerDeprecated][nslookup is no longer to be treated as deprecated. Remove "deprecated" warning message.]

実際、何もトラブルが起きておらず、単純に名前解決した結果を知りたいだけであればhostやnslookupでも事足ります。ですがトラブル発生時の調査手段としてhostやnslookupを使おうとすると、必要な情報が不足していたり調べてきた結果を下手に加工して出力したりするため、どちらもあまり使いやすいコマンドとは言えません。これを機に今後はdigを使っていきましょう！

== Whoisを叩いてドメインやIPの持ち主を調べよう

whoisコマンドを使うと、@<chapref>{domain}でお話ししたようなWhois情報を調べることができます。しかもwhoisコマンドはドメインの持ち主だけでなく、IPアドレスの持ち主を調べることもできます。

//cmd{
ドメインの持ち主を調べる
$ whois ドメイン

IPアドレスの持ち主を調べる
$ whois IPアドレス
//}

=== 【ドリル】ドメインの有効期限が分からない

==== 問題

あなたはかき氷を作れるきょろちゃん@<fn>{kyoro}のサイト運用担当者です。（@<img>{kyoro}）

//image[kyoro][きょろちゃん][scale=0.8]{
//}

このたび運用担当を新人へ引き継ぐことになりました。引継ぎ資料を読んだ新人から「ここに毎年ドメインの更新作業が必要って書いてあるんですけど、次の更新っていつごろですか？」と聞かれました。ドメインの有効期限を知るにはどのコマンドを叩けばいいですか？

//footnote[kyoro][@<href>{http://tigerkyoro.jp/}]

 * A. dig tigerkyoro.jp +short
 * B. whois tigerkyoro.jp

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はBです。whoisコマンドを叩くと「Expires on」という項目に有効期限が表示されます。今回のtigerkyoro.jpであれば、次のようにwhoisコマンドを叩けば、有効期限が2019/01/31であることが分かります。

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
[Expires on]                    2019/01/31
[Status]                        Active
[Last Updated]                  2018/02/01 01:05:08 (JST)

Contact Information:
[Name]                          Clarivate Analytics (Japan) Co.,Ltd.
[Email]                         admin@thomsonbrandy.jp
[Web Page]
[Postal code]                   107-6119
[Postal Address]                Akasaka Park Building, 19F,
                                5-2-20, Akasaka,Minato-ku,Tokyo
[Phone]                         03-4589-3900
[Fax]                           03-4589-3240
//}

== digを叩いてリソースレコードを確認してみよう

ここからは調べたい内容に応じて、どうdigコマンドを叩けばいいのか？を1つ1つ確認していきます。digを叩いてもサーバは壊れないし、地球も爆発しません。軽い気持ちでどんどん叩いてdigに慣れていきましょう。

=== Aレコード

たとえば「www.example.jpは203.0.113.222」や「mx.example.comは203.0.113.22」のように、ドメインとIPアドレスを紐づけているのがAレコードです。あなたが「このサイトはどこにあるんだろう？」と思ったら、次のようにdigコマンドを叩いてみましょう。@<fn>{prompt}するとそのドメインに紐づくIPアドレスが表示されるはずです。

//cmd{
$ dig ドメイン名 a +short
//}

//footnote[prompt][一番左の「$」はサーバにログインしたときにユーザ名やサーバの名前が表示される「プロンプト」というものを表しています。この「$」は実際は入力しなくていいので、dig以降を入力してください。]

=== 【ドリル】ウェブサーバはどこにある？

==== 問題

あなたは「mojimo-manga」（モジモマンガ）というサイト（@<href>{https://mojimo.jp/manga/}）の運用担当になりました。@<fn>{exampleSite}（@<img>{mojimoManga}）

ところが前任者が急に辞めてしまって引継ぎ資料も見当たらず、このサイトがどこのウェブサーバで動いているのかちっとも分かりません。

//footnote[exampleSite][もちろん例えです。本著及び著者は例えに使用させていただいたサイトと何の関係もありません。]

//image[mojimoManga][mojimo-manga - あのマンガの、あのアニメの、あのフォントが使える！][scale=0.8]{
//}

ウェブサーバはどこのクラウドサービスを使っているのでしょうか？

 * A. さくらインターネット
 * B. AWS
 * C. IDCFクラウド

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はBです。

先ず「dig ドメイン名 a +short」でドメインからIPを引いてみましょう。サイトのURLが@<href>{https://mojimo.jp/manga/}なので、確認すべきドメインはmojimo.jpです。

//cmd{
$ dig mojimo.jp a +short
46.51.255.231
54.248.233.139
//}

IPアドレスは分かりましたが、IPだけではまだどこのクラウドサービスなのか分かりません。さらにwhoisコマンドでこのIPアドレスの持ち主を調べてみましょう。@<fn>{twoIp}

「whois 46.51.255.231」を叩いてみると「descr: Amazon Web Services, Elastic Compute Cloud, EC2」と出ますので、このIPアドレスはAWSのEC2のものであることが分かります。これでmojimo-mangaのサイトがAWSのEC2上で動いていることが分かりました。

//footnote[twoIp][IPアドレスは2つありますがどちらでも構いません。]

//cmd{
$ whois 46.51.255.231
（中略）
descr:          Amazon Web Services, Elastic Compute Cloud, EC2
country:        JP
admin-c:        ADSI2-RIPE
tech-c:         ADSI2-RIPE
status:         ASSIGNED PA
mnt-by:         MNT-ADSI
mnt-by:         NN20150720
created:        2017-11-07T20:48:28Z
last-modified:  2017-11-07T20:49:00Z
source:         RIPE
（後略）
//}

===[column] 【コラム】digのオプションは略せる

digコマンドには「+short」や「+norecurse」のようなクエリオプションがありますが、それぞれ後ろの何文字かを省略して「+shor」や「+norec」でも実行可能です。

このような「コマンドオプションって略せるの？！」といったdigの細かい仕様や仕組みをもっと詳しく知りたい！という方は、JPRSが公開している「初心者のためのDNS運用入門 - トラブル事例とその解決のポイント -」@<fn>{dnsBeginner}という資料がお勧めです。

//footnote[dnsBeginner][@<href>{https://dnsops.jp/event/20140626/dns-beginners-guide2014-mizuno.pdf}]

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

MXレコードから察するに任天堂はOffice 365@<fn>{office365}を使っているようです。さらに「nintendo-co-jp.mail.protection.outlook.com」のAレコードを引くと、最終的にはメール受信サーバのIPアドレスまでたどり着くことができます。

//footnote[office365][Microsoftの法人向けサービス。メールやグループウェア、Microsoft Officeなどを利用できる。]

//cmd{
$ dig nintendo-co-jp.mail.protection.outlook.com a +short
23.103.139.138
23.103.139.170
//}

==== MXレコードがなければ代わりにウェブサーバ宛てにメールが届く

ところで、もしMXレコードが存在しなかったらどうなるのでしょう？メールを送ろうとしたとき、そのドメインのMXレコードが存在しなかったらメールを送信できない・・・・のではなく、代わりにAレコードで紐づけられているIPアドレスに対してメールを送ろうとします。@<fn>{rfc5321}

//footnote[rfc5321][@<href>{https://tools.ietf.org/html/rfc5321#section-5.1}]

つまり「今回は@<href>{http://example.co.jp/}というサイトを開くだけでメールを送受信する要件は全くないのでexample.co.jpのMXレコードは設定しません」と思っていても、example.co.jpのAレコードさえあれば、そこに書かれたウェブサーバに対してメールが飛んできてしまう可能性があるのです。Postfix@<fn>{postfix}はCentOSを最小限の構成でインストールしたときでも入っているので、全然意図していなかったけれどうっかりウェブサーバでPostfixが動いていて、エンドユーザから送られてきた個人情報満載なメールをひっそり受信していた！という可能性もあります。

//footnote[postfix][メール転送エージェント。要はメールを受信したり送信したりするためのメールサーバ。]

そのドメインでメールを受信する予定がないのであれば、次のようにプリファレンス値を「0（ゼロ）」、メールサーバ名を「.（ドット）」にしたNull MX@<fn>{nullMx}を設定することで「メールを受信しません」という意図を明示しておく方が、メールを送る側も受信する側にも余計な負担がなくなってよいかも知れません。

//footnote[nullMx][@<href>{https://tools.ietf.org/html/rfc7505}]
//cmd{
example.co.jp.    IN  MX    0  .
//}

ただし、メールを受信する要件がなかったとしても、メールを送信する要件がある場合はバウンスメール@<fn>{bounceMail}受信のためにMXレコードを設定しておくべきです。

//footnote[bounceMail][宛先のメールアドレスが間違っていた、などの理由でメールが正常に配信できなかった場合に送信元に対して戻ってくるメールのこと。MAILER-DAEMONやリターンメール、エラーメールとも呼ばれる。]

=== ＜トラブル＞test@test.co.jpを使って情報漏洩

あなたは広告代理店B社のプロデューサーで、A社の新製品である花粉症用マスクの先行体験キャンペーンを企画・担当しています。

キャンペーンサイトのフォームから新製品の先行体験キャンペーンに申し込むと、お客様には「応募を受け付けました」というメールが届きます。このメールにはお客様がフォームで記入された住所や電話番号などが書いてあります。

この受付完了メールですが、実は送信元メールアドレス（From）を何にするか、実装が始まった時点では仕様が決まっていませんでした。そのため送信元メールアドレスは、ディレクターが仕様書に取り合えずのつもりで書いておいたinfo@test.co.jpというアドレスで実装されてしまい、テストでも誰も気づかないまま本番リリースを迎えてしまいました。

キャンペーンが始まり、花粉症のCさんは早速フォームから申し込みました。しかしCさんは最近引っ越したばかりだったので、うっかり古い住所をフォームで送ってしまいました。「応募を受け付けました」メールを見て住所が間違っていることに気づいたCさんは、すぐにメールの返信でinfo@test.co.jp宛てに「入力した住所が間違っていました。正しい住所は〇〇なので訂正したいです」という問い合わせを送りました。

しかしいつまで経っても返事が来ません。Cさんがキャンペーン事務局にクレームの電話を入れてエンジニアのDさんが調査をした結果、送信元メールアドレスがA社ではなくinfo@test.co.jpになっていた問題が発覚しました。果たしてCさんがinfo@test.co.jp宛てに送ったメールはどこへ行ってしまったのでしょう？

プロデューサーのあなたもエンジニアのDさんと一緒にこの問題を調査してみましょう。メール受信サーバを知りたいときは「dig ドメイン名 mx +short」です。

//cmd{
$ dig test.co.jp mx +short
10 mail10.heteml.jp.
//}

Cさんがinfo@test.co.jp宛てに送ったメールを受信しているのはmail10.heteml.jpであることが分かりました。mail10.heteml.jpについてウェブで検索してみたところ、どうやらGMOペパボがやっているヘテムル@<fn>{heteml}というクラウドサービスのメールサーバのようです。

//footnote[heteml][@<href>{https://heteml.jp/}]

〇〇@test.co.jpに送ったメールはヘテムルで受信している、というところまで分かりましたが、そもそもtest.co.jpというドメインは誰の持ち物なのでしょうか？今度はwhoisでドメインの持ち主を調べてみましょう。

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
[State]                         Connected (2019/02/28)
[Registered Date]               2000/02/14
[Connected Date]                2000/02/16
[Last Update]                   2018/03/01 01:05:12 (JST)
//}

Whoisで調べてみるとこのドメインは「EDUCATIONAL ASSESSMENT INSTITUTE LIMITED COMPANY」という名前の有限会社の持ち物である、という情報が出てきました。プロデューサーのあなたとエンジニアのDさんはなんだか嫌な予感がして、ブラウザで@<href>{http://test.co.jp/}（@<img>{testCoJp}）を開いてみました。すると有限会社教育評価研究所という会社のウェブサイトが表示されました。

//image[testCoJp][教育評価研究所][scale=0.8]{
//}

なんと花粉症のCさんがinfo@test.co.jp宛てに送ったお問い合わせメールは、クライアントのA社とも広告代理店のB社とも何の関係もない有限会社教育評価研究所という会社に飛んでしまったようです。「エンドユーザの個人情報漏洩だ、やってしまった・・・」とあなたとDさんは頭を抱えました。

==== 自分のものでないドメインを使うべきでない理由

このように「自分の持ち物でないドメイン」を勝手に使うのはトラブルの元です。

 * test.co.jp
 * test.com
 * aaa.com
 * xxx.com

などはいかにもサンプルっぽいので、なんとなく「田中一郎」や「山田太郎」のようなノリで使いたくなってしまいますが、これらのドメインにはいずれもちゃんと持ち主@<fn>{exampleDomain}がいます。

//footnote[exampleDomain][たとえば「test.com」というドメインはDOSarrestというサービスをやっている Internet Security LTD,という会社が持ち主ですし、前述のとおりtest.co.jpというドメインは有限会社教育評価研究所という会社が持ち主です。]

そのためたとえば宅配ピザのステージングサイトで、仮にtanaka@test.co.jpというメールアドレスのテストユーザを作ってテストを行うと、実際に有限会社教育評価研究所という会社に会員登録完了メールや注文完了メールが飛んでいってしまい、相手方にご迷惑であると共に情報漏洩の恐れもあります。なかなかぴんと来ないかも知れませんが、誰かがアンケートに適当な住所を書いたせいで全然関係ない自分の家にダイレクトメールが届いたら迷惑ですよね。

ありがちですがお問い合わせフォームのメールアドレスの例にsample@test.comのように書くのもやめましょう。銀行に行って申請用紙のサンプルに自分の住所が部屋番号までばっちり書かれていたらぎょっとしますよね？それと同じことです。実在する他人の住所や電話番号を勝手に使わないのと同じように、他人のドメインも勝手に使わないようにしましょう。

==== 例示やテスト専用のドメインを使おう

他人が持っているドメインを勝手に使ってはいけない、ということは分かりました。では誰のものでないドメインならいいのでは？と思われるかも知れませんが、現時点で誰のものでもなくても明日には誰かがそのドメインを取得するかも知れませんのでこれもやはりお勧めしません。

じゃあどうしたらいいのかというと、実はインターネットでは「例示やテストで使っていいドメイン」というものが定められて@<fn>{rfc2606}います。テストユーザのメールアドレスや、フォームで例として書くメールアドレスには次のドメインを使いましょう。

 * example.co.jp
 * example.jp
 * example.com
 * example.net

//footnote[rfc2606][RFC2606で定められているexample.comやexample.net、もしくはJPRSが定めているexample.jpやexample.co.jpなどを使いましょう。@<href>{https://jprs.jp/faq/use/}]

これらのドメインであれば将来的に誰かのものになる可能性もありませんし、リソースレコードはMXレコードもAレコードも設定されていないため、予期せぬ第三者へうっかりメールが飛んでいってしまうことは避けられます。

=== NSレコード

ドメインのネームサーバを指定しているのがNSレコードです。キャンペーンサイト用にサブドメインを増やしたいけど、サブドメインってどこで作ればいいんだっけ？というときは次のようなdigコマンドを叩いてNSレコードを調べればわかります。

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
ns-390.awsdns-48.com.
ns-1487.awsdns-57.org.
ns-1984.awsdns-56.co.uk.
ns-692.awsdns-22.net.
//}

ゾーンの中のリソースレコードを確認するにはAWSのマネジメントコンソールにログインする必要がありますが、AWSアカウント名やパスワードまではさすがにdigでは分からないので、そこはなんとか過去資料から探してください。またRoute53にはホストゾーンのエクスポート機能がないので、リソースレコードを1つ1つコピーペーストするかCLI@<fn>{cli}を駆使して取得する必要があります。

//footnote[cli][コマンドラインインターフェイスの略。AWSはブラウザでぽちぽち操作するだけでなく、CLIを用いてコマンドラインからも操作できます。]

=== SPFレコード（TXTレコード）

AさんがBさんに手紙を書くとき、封筒の差出人欄に「Cさんより」と書けば簡単に送信元を騙ることができます。メールもそれと同じで、送信元のメールアドレスを詐称して送信することは容易です。迷惑メールの多くはこのように送信元を詐称しているなりすましメールです。

このとき送り主が本物なのか、あるいは自分の持ち物でないドメインで送信元を詐称して勝手にメールを送っている「なりすましメール」なのかを確認する手段として、SPF@<fn>{spf}レコードというものがあります。SPFレコードは次のdigコマンドで確認できます。

//footnote[spf][Sender Policy Frameworkの略。]

//cmd{
$ dig ドメイン名 txt +short
//}

SPFレコードなのにtxtなの？と疑問に思われるかも知れません。昔はSPFを設定する方法としてSPFレコードとTXTレコードという2種類のリソースレコードに書くことが推奨されていたのですが、SPFレコードに書く方法は普及せず、最終的に「SPFはTXTレコードで設定すること」となりました。@<fn>{rfc7208}

//footnote[rfc7208][@<href>{https://tools.ietf.org/html/rfc7208#section-3.1}でSPF records MUST be published as a DNS TXT (type 16) Resource Record(RR) [RFC1035\] onlyと書かれています。]

たとえばポケモンだいすきクラブ@<fn>{pokemon}から届く「ポケモンだいすき！通信」というメールは、送信元のメールアドレスがnoreply@pdc.pokemon.jpです。pdc.pokemon.jpのSPFレコードを確認してみましょう。

//footnote[pokemon][ポケモンの情報サイト。ミミッキュのうたは名曲です。@<href>{http://www.pokemon.jp/}]

//cmd{
$ dig pdc.pokemon.jp txt +short
"v=spf1 include:spf.pdc.pokemon.jp include:spf.pokemon.mailds.jp ~all"
//}

includeは引数で渡しているドメインのSPFレコードを含むという意味ですので、さらにspf.pdc.pokemon.jpとspf.pokemon.mailds.jpのSPFレコードを引いてみましょう。

//cmd{
$ dig spf.pdc.pokemon.jp txt +short
"v=spf1 +ip4:203.216.217.0/24 +ip4:122.212.36.0/24 +ip4:202.8.80.0/23
 +ip4:202.74.4.160/27 +ip4:59.159.71.0/24 +ip4:220.110.139.188/32
 +ip4:211.120.127.41/32 +ip4:125.29.35.0/26 +ip4:124.211.29.64/26
 +ip4:122.215.202.64/26 +ip4:203.138.159.219 ~all"

$ dig spf.pokemon.mailds.jp txt +short
"v=spf1 ip4:118.238.144.96/29 ip4:118.238.144.120/30 ~all"
//}

一番最初の「+ip4:203.216.217.0/24」は「203.216.217.0～203.216.217.255のIPアドレスをメールの送信元サーバとして認める」という意味です。ひとつひとつ解説するには量が多すぎるので省略しますが、要はここに書いてあるIPから届いたメールは本物で、それ以外は恐らく迷惑メールだよ、ということを示しています。実際に届いた「ポケモンだいすき！通信」の送信元IPは「118.238.144.99」でしたので、きちんとSPFレコードの中に含まれており、メールは迷惑メール扱いされることなく受信ボックスに届きました。

=== 【ドリル】どうしてメールが迷惑メール扱いされるの？

==== 問題

あなたはWeb制作会社A社のフロントエンドエンジニアです。小規模なクライアントB社からの依頼でキャンペーンサイト（@<href>{http://campaign.example.com/}）を構築したのですが、後から「問い合わせフォームが欲しい」という追加要望が出てきました。

予算もあまりないためフォームは実装せず、問い合わせのページだけは簡単にフォームが作れる外部のASPサービスを使うことにしました。エンドユーザがフォームから問い合わせを行うと、そのASPサービスがB社とエンドユーザの両方に「問い合わせを受け付けました」というメールを送ってくれます。このとき送信元のメールアドレスは「info@example.com」です。

ところがB社の担当者から「問い合わせ受付メールが迷惑メール扱いされて迷惑メールボックスに入ってしまう。エンドユーザの方でも同じ現象が起きているようだ」というクレームが入りました。原因を調査するにはどのdigコマンドを叩くべきでしょうか？

 * A. dig example.com spf +short
 * B. dig campaign.example.com txt +short
 * C. dig example.com txt +short

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はCです。送ったメールが迷惑メール扱いされてしまうときは「dig ドメイン名 txt +short」でSPFレコードを確認しましょう。SPFレコードには、そのドメインでのメール送信を許可されているサーバのリストが書かれています。

今回、問い合わせ受付メールが迷惑メール扱いされてしまったのは、SPFレコードにメールを送っているサーバのIPアドレスを追加し忘れたことが原因と思われます。ASPサービスにメール送信元のIPアドレスを確認して、SPFレコードに追記しましょう。

=== PTRレコード

Aレコードは前述のとおりドメインからIPアドレスを正引きできるレコードです。対してIPアドレスからドメインを逆引きできるレコードのことをPTRレコード@<fn>{ptr}と呼びます。

//footnote[ptr][PoinTeR recordの略。]

メールを受信するメールサーバによっては「メール送信元のIPアドレスがSPFレコードに登録されていること」だけでなく「メール送信元のIPアドレスからドメインの逆引きができること」という条件も満たさないと迷惑メールと判断することがあります。

PTRレコードは次のdigコマンドで確認できます。

//cmd{
$ dig -x IPアドレス +short
//}

なおAレコードやMXレコードやSPFレコードといったドメインのリソースレコードと、PTRレコードのようなIPアドレスのリソースレコードは設定依頼をする先が異なります。筆者はstartdns.funというドメインを持っており、ネームサーバはRoute53を使用しているので、startdns.funのAレコードやMXレコード、SPFレコードはRoute53で設定ができます。

ですが、たとえばさくらインターネットのVPSで借りたサーバのIPアドレスが203.0.113.222だったとして、このIPのPTRレコードをRoute53で設定することはできません。このIPに対してPTRレコードを設定できるのは、IPアドレスの持ち主であるさくらインターネットの管理画面からとなります。

=== CNAMEレコード

ときどきドメインからIPアドレスを引こうとしてdigでAレコードを調べたのに、こんな風にドメインとIPアドレスが返ってくることがあります。

//cmd{
$ dig aibo.sony.jp a +short
cs1018.wpc.omicroncdn.net.
152.195.38.205
//}

なぜaiboのサイト@<fn>{aibo}のAレコードを調べるとcs1018.wpc.omicroncdn.netという全然関係のなさそうなドメインが出てくるのでしょう？+shortオプションを外して、この結果に至るまでの過程を見てみましょう。

//footnote[aibo][@<href>{https://aibo.sony.jp/}]

//cmd{
$ dig aibo.sony.jp a

; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.62.rc1.el6_9.5 <<>> aibo.sony.jp a
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 58537
;; flags: qr rd ra; QUERY: 1, ANSWER: 2, AUTHORITY: 2, ADDITIONAL: 4

;; QUESTION SECTION:
;aibo.sony.jp.                  IN      A

;; ANSWER SECTION:
aibo.sony.jp.           300     IN      CNAME   cs1018.wpc.omicroncdn.net.
cs1018.wpc.omicroncdn.net. 3091 IN      A       152.195.38.205

;; AUTHORITY SECTION:
omicroncdn.net.         172518  IN      NS      ns2.omicroncdn.net.
omicroncdn.net.         172518  IN      NS      ns1.omicroncdn.net.

;; ADDITIONAL SECTION:
ns1.omicroncdn.net.     172518  IN      A       72.21.80.5
ns1.omicroncdn.net.     172518  IN      AAAA    2606:2800:1::5
ns2.omicroncdn.net.     172518  IN      A       72.21.80.6
ns2.omicroncdn.net.     172518  IN      AAAA    2606:2800:1::6

;; Query time: 0 msec
;; SERVER: 127.0.0.1#53(127.0.0.1)
;; WHEN: Mon Mar 19 22:09:15 2018
;; MSG SIZE  rcvd: 209
//}

ANSWER SECTIONを見てみましょう。aibo.sony.jpのCNAMEレコードにcs1018.wpc.omicroncdn.netが設定されており、さらにcs1018.wpc.omicroncdn.netのAレコードに152.195.38.205が設定されていることが分かります。このとき「aibo.sony.jp」をaliases（別名）、「cs1018.wpc.omicroncdn.net」をcanonical name（正式名）と呼びます。

フルリゾルバはaibo.sony.jpのAレコードを調べに行って、Aレコードの代わりにCNAMEレコードが見つかった場合、名前解決の対象を正式名であるcs1018.wpc.omicroncdn.netに置き換えて引き続きAレコードを調べ、最終的にcs1018.wpc.omicroncdn.netのAレコードに紐づくIPアドレスを返してきます。

このようにCNAMEレコードが設定されているときは、Aレコードを問い合わせても結果としてCNAMEレコードと、その正式名のAレコードの両方が返ってきますが、CNAMEレコードだけを調べたいときは次のdigコマンドで確認できます。

//cmd{
$ dig ドメイン名 cname +short
//}

=== 【ドリル】CNAMEの調べ方と使いどころ

==== 問題

キドキド@<fn>{kidoKidUrl}のサイト（@<img>{kidokid}）のドメイン「kidokid.bornelund.co.jp」のCNAMEレコードを知りたい場合、どのdigコマンドを叩けばよいでしょうか？

//footnote[kidoKidUrl][@<href>{https://kidokid.bornelund.co.jp/}]

//image[kidokid][キドキド（KID-O-KID）のサイト][scale=0.8]{
//}

 * A. dig kidokid.bornelund.co.jp cname +short
 * B. dig kidokid.bornelund.co.jp a +short
 * C. dig kidokid.bornelund.co.jp txt +short
 * D. dig kidokid.bornelund.co.jp mx +short

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はAです。ただしBもCNAMEレコードとそのAレコードが返ってくるので、Bも正解で構いません。CNAMEレコードはCDN@<fn>{cdn}を使うときによく利用されます。

//footnote[cdn][Contents Delivery Networkの略。アクセスしてきたエンドユーザに最も近いサーバからサイトのコンテンツを効率的に配信できる仕組みのこと。CDNを使うとエンドユーザからのアクセスが分散されるため、TVCMやLINE砲で一気にアクセスが殺到してもサイトが落ちたり重くなったりしないで済みます。]

//cmd{
$ dig kidokid.bornelund.co.jp cname +short
bornelund-ELB-1960389134.ap-northeast-1.elb.amazonaws.com.
//}

CDNを使う場合だけでなく、1台のウェブサーバに大量のサイトが相乗りしているような場合もCNAMEレコードを使うと便利です。たとえばウェブサーバにサイトA、サイトB、サイトC・・・と計100サイトが相乗りしていてそれぞれAレコードを設定していた場合、ウェブサーバを引っ越すとなったら100件のAレコードを書き換えなければなりません。ですが、Aレコードを設定しているのはサイトAのみで、それ以外のサイトはCNAMEでサイトAのドメインを指定するという方法にしておけば、サーバ引っ越しに際して書き換えなければならないのはサイトAのAレコードのみです。

=== CNAMEと他のリソースレコードは共存できない

一見便利なCNAMEレコードですが使用する際は注意点があります。それは「@<b>{CNAMEレコードを設定したら、他のリソースレコードは設定できない}」ということです。

たとえば次のようなCNAMEレコードとMXレコードは共存ができません@<fn>{rfc1912}。

//footnote[rfc1912][A CNAME record is not allowed to coexist with any other data. @<href>{http://www.ietf.org/rfc/rfc1912.txt}]

//cmd{
campaign.example.com.   IN   CNAME    cdn.example.jp.
campaign.example.com.   IN   MX       mail.example.com.
//}

campaign.example.comのCNAMEレコードでcdn.example.jpを設定すると、AレコードだけでなくMXレコードもTXTレコードもNSレコードも、ありとあらゆるリソースレコードがcdn.example.jpを参照しに行ってしまいます。そのため2行目でcampaign.example.comのMXレコードでmail.example.comを設定しても、そのMXレコードは名前解決に使われることなく無視されてしまうのか、あるいは使われるのか動作が全く保証されません。

このような理由からRoute53をはじめとするネームサーバのサービスでは、CNAMEレコードを設定した場合は他のリソースレコードが設定できないようになっています。

また「ありとあらゆるレコード」にはCNAMEレコードも含まれるため、次のようにCNAMEレコードを複数設定することもできません。

//cmd{
campaign.example.com.   IN   CNAME    cdn1.example.jp.
campaign.example.com.   IN   CNAME    cdn2.example.jp.
//}

==== ZONE APEXはCNAMEを使えない

前述の「CNAMEレコードは他のリソースレコードと共存できない」という理由から、@<idx>{ZONE APEX}@<fn>{zoneApex}ではCNAMEを設定することができません。筆者がCDNを使いたいと思っても、次のようなCNAMEレコードは設定できないのです。

//footnote[zoneApex][startdns.funやexample.jpのようにwwwやstgといったサブドメインを含まないドメインのこと。レジストラやリセラで買ったいちばん短い表記のドメインのことをZONE APEXと呼びます。Apex DomainやNaked Domain、ホスト名なしドメインなどと呼ばれることもあります。]

//cmd{
startdns.fun.   IN   CNAME    cdn.example.jp.
//}

なぜならばCNAMEレコードが他のリソースレコードと共存できないのに対して、ZONE APEXには「このドメインはこのネームサーバを使うよ」というNSレコード、および「このドメインの管理情報はこれだよ」というSOAレコードが必ず存在するからです。（お名前.comで自分のドメインを買った後、Route53でホストゾーンを作成したらSOAレコードとNSレコードが自動生成されていたのを覚えていますか？）

==== Route53のAliasレコードならZONE APEXでも設定可能

前述の「CNAMEレコードは他のリソースレコードと共存できない」「ZONE APEXにはNSレコードとSOAレコードが必ず存在する」という2つの制限から、たとえCDNやELB@<fn>{elb}を使いたいと思ってもZONE APEXでは使用できなかったのですが、なんとRoute53のAliasレコードという独自拡張を使うとZONE APEXでもCDNを使うことができるのです。@<fn>{alias}

//footnote[elb][Elastic Load Balancingの略。AWSのサービスの1つでいわゆるロードバランサーのことです。]
//footnote[alias][Route53のAliasの他にCloudFlareのCNAME Flatteningなど類似のサービスはいくつかあります。]

しかもAliasレコードには「ZONE APEXでも使える」だけでなく、「CNAMEと違って名前解決が1回で済む」という利点があります。

たとえばstartdns.funというドメインに紐づくIPアドレスを調べようとしたとき、CNAMEレコードの場合は「startdns.funのCNAMEレコードはcdn.example.jpで、cdn.example.jpのAレコードは203.0.113.222」のように名前解決が2回発生します。対してRoute53のAliasレコードで「startdns.funのエイリアス先はcdn.example.jpである」という設定をしておけば、フルリゾルバがstartdns.funのAレコードを問い合わせに来たら「startdns.funのAレコードは203.0.113.222」のように一発でIPアドレスを返すので名前解決は1回で済みます。


ネームサーバでRoute53を使っていても、参照先のCDNやロードバランサーがAWS外なのであればCNAMEを使うしかありませんが、参照先がAWS内のサービスであればAliasレコードを使わない手はありません。ZONE APEXに限らず積極的に使いましょう。

=== グルーレコード

ところでドメインを買ったとき、お名前.comのネームサーバやRoute53を使う他に自力でネームサーバを立てて使うこともできます。Linuxサーバを立ててApacheをインストールすればウェブサーバになるように、Linuxサーバを立ててBINDをインストールすればもうそれは立派なネームサーバです。

たとえば筆者がstartdns.funというドメインを買って、自分で作ったネームサーバにns1.startdns.funという名前を付け、startdns.funのNSレコードにns1.startdns.funを設定したとします。このとき、ブラウザで@<href>{http://startdns.fun/}を開こうとすると次のようになります。

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

これを解消するため、自分でネームサーバを立てるときは上位のDNSコンテンツサーバ（ここではa.nic.funのこと）に、ネームサーバのIPアドレスも一緒に登録しておかなければいけません。これをグルーレコードと呼びます。上位のa.nic.funからns1.startdns.funへの道をちゃんと繋げてくれるレコードだからglue（接着剤のこと）レコードなんですね。

お名前.comであればドメインNaviの中に「ネームサーバー名としてのホストを設定する」という設定画面がありますので、そこで自分が立てたネームサーバのドメイン名（ns1.startdns.fun）とそのIPアドレス（203.0.113.222）を登録すればOKです。これでいつまでもns1.startdns.funにたどり着けない無限ループが回避できるようになります。
