= AWSのネームサーバ（Route53）を使ってみよう

@<chapref>{domain}で自分のドメイン名を買って、@<chapref>{whatIsDns}ではDNSの仕組みを学びました。
この章ではAWSのRoute53（ルートフィフティースリー）というDNSサービスで自分のドメイン名のゾーンやリソースレコードを作ってみましょう。

//pagebreak

== AWSとは

AWSとはアマゾン ウェブ サービス（Amazon Web Services）の略で、欲しいものをぽちっとな！すると翌日には届くあのアマゾンがやっているクラウドです。

アマゾンがやっているクラウドと言われても、そもそもクラウドってなんだろう？という方もいますよね。クラウドとは「ブラウザ上でスペックを選んでぽちぽちっとするだけで誰でもすぐにウェブサーバやDBサーバを立てたりネームサーバを使ったりできるサービス」@<fn>{cloud}のことです。AWSでは基本的に1秒単位の従量課金なので、たとえばサーバを立てて3分使ったら3分ぶんのお金しかかかりません。

//footnote[cloud][AWSやクラウド、サーバについては本著の続編「AWSをはじめよう」で詳しく解説していますので、ここでは正確さよりも分かりやすさを優先したゆるい説明にしています。]

今回はAWSの中でもRoute53（ルートフィフティースリー）というDNSのサービスを使用します。クラウドといえばGoogleのGoogle Cloud PlatformやMicrosoftのAzure（アジュール）、最近シェアを伸ばしてきたAlibaba Cloud、さくらインターネットのクラウドやGMOクラウドなどAWS以外にもたくさんあります。ですが現状のシェアトップはダントツでAWS@<fn>{cloudShare}です。AWSなら何か困って検索したときに出てくる情報も多いので、今回はAWSのRoute53でドメインのゾーンを作成します。

//footnote[cloudShare][2018年時点、AWSはシェア全体の3割以上を占めクラウド界のトップを独走中です。]

== AWSアカウント作成

先ずはAWSのアカウントを作りますので次の2つを用意してください。

 * クレジットカード
 * 通話可能な携帯電話（電話番号認証で使用するため）

なおAWSを初めて使用する場合、利用料が1年分無料@<fn>{awsFree}となります。

//footnote[awsFree][無料利用枠の範囲が決まっており、何をどれだけ使っても無料という訳ではありませんので注意してください。たとえばこの後利用するRoute53というDNSのサービスは、1つのドメインにつき毎月50セントかかります。詳細は@<href>{https://aws.amazon.com/jp/free/}を確認してください。]

「AWS 無料」（@<img>{searchAwsFree}）で検索して上から2つめの「AWS クラウド無料利用枠 | AWS」@<fn>{awsFreeUrl}をクリックします。

//image[searchAwsFree][「AWS 無料」で検索][scale=0.8]{
//}

//footnote[awsFreeUrl][@<href>{https://aws.amazon.com/jp/free/}]

「AWSクラウド無料利用枠」（@<img>{startAwsForFree}）のページを開いたら、「まずは無料で始める」をクリックします。

//image[startAwsForFree][「まずは無料で始める」をクリック][scale=0.8]{
//}

AWSアカウントの作成画面（@<img>{signupAws}）で次の4つを入力したら、「続行」をクリックします。後で分からなくならないように、何を登録したのかはメモしておいてください。

 * Eメールアドレス
 * パスワード
 * パスワードの確認
 * AWSアカウント名

//image[signupAws][メールアドレスとパスワードとAWSアカウント名を記入して「続行」を押す][scale=0.8]{
//}

連絡先情報（@<img>{registUserData01}・@<img>{registUserData02}）はすべて英語表記で登録します。今回は仕事ではなく個人での利用ですのでアカウントの種類は「パーソナル」を選択してください。住所と電話番号を記入したら「AWSカスタマーアグリーメントの同意」にチェックを入れて「アカウントを作成して続行」を押します。

//image[registUserData01][連絡先情報は英語で登録][scale=0.8]{
//}

//image[registUserData02][連絡先を入力したら「アカウントを作成して続行」を押す][scale=0.8]{
//}

前述のとおり、AWSを初めて使用する場合は利用料が1年分無料なのですが、クレジットカードは登録しておく必要があります。支払情報（@<img>{paymentInfo01}・@<img>{paymentInfo02}）にクレジットカード情報を記入して「連絡先住所を使用する」を選択したら「セキュアな送信」を押します。

//image[paymentInfo01][クレジットカード情報を記入][scale=0.8]{
//}

//image[paymentInfo02][請求先住所を選択して「セキュアな送信」を押す][scale=0.8]{
//}

電話による確認（@<img>{phoneCall}）で電話番号（例：090-1234-5678）とセキュリティチェックのCaptchaを入力したら、携帯電話を手元に用意した状態で「すぐに連絡を受ける」を押します。

//image[phoneCall][電話番号とCaptchaを入力したら「すぐに連絡を受ける」を押す][scale=0.8]{
//}

このとき「エラー：お支払情報に問題があります」（@<img>{paymentError}）と表示されて、何度試しても電話確認に進めない場合があります。AWSでは初回登録時に「1ドル認証」と呼ばれる認証方法でクレジットカードが決済可能かをチェックしているのですが、クレジットカードによってはこの1ドル認証を不審な決済と判断して通さないため、それによってエラーが発生することがあるようです。その場合は別のクレジットカードで試すか、AWSのチャットサポートで問い合わせてみてください。

//image[paymentError][クレジットカードに起因するエラー][scale=0.8]{
//}

「すぐに連絡を受ける」を押すとすぐに通知不可能で電話（日本語の自動音声）がかかってくるので、パソコン側で表示されている4ケタの番号（@<img>{enterNumber}）を電話でプッシュしてください。

//image[enterNumber][パソコンで表示された4ケタの番号を電話でプッシュ][scale=0.6]{
//}

確認完了して電話が切れたら、パソコン側で「本人確認が終了しました」（@<img>{userCheckEnd}）と表示されるので「続行」を押します。

//image[userCheckEnd][「本人確認が終了しました」と表示されたら「続行」を押す][scale=0.6]{
//}

本人確認が完了したらサポートプランの選択に進みます。サポートプランの選択（@<img>{supportPlan}）はベーシックプランがよいので、いちばん左の「無料」を押します。

//image[supportPlan][サポートは無料のベーシックプランを選択][scale=0.8]{
//}

「アマゾン ウェブ サービスへようこそ」（@<img>{welcomeToAws}）と表示されたらAWSのアカウント作成は完了です。おめでとうございます！「コンソールにサインインする」ボタンを押して次のステップへ進みましょう。

//image[welcomeToAws][AWSのアカウント作成完了][scale=0.8]{
//}

=== AWSのマネジメントコンソールにログイン

「コンソールにサインインする」を押す@<fn>{console}と、マネジメントコンソールへのログイン画面が表示されます。（@<img>{signInMailAddress}）先ほど登録したAWSアカウントのEメールアドレスを入力して「次へ」を押してください。

//footnote[console][後でまたマネジメントコンソールにログインしたくなったら@<href>{https://aws.amazon.com/}で「コンソールへサインイン」を押せばログイン画面が表示されます。]

//image[signInMailAddress][AWSのアカウントのEメールアドレスを入力][scale=0.8]{
//}

続いてルートユーザーサインインの画面（@<img>{rootUserSignIn}）でパスワードを入力したら「サインイン」を押します。

//image[rootUserSignIn][パスワードを入力してサインイン][scale=0.8]{
//}

無事にログインできたら、マネジメントコンソールというAWSの管理画面（@<img>{managementConsole}）が表示されます。

//image[managementConsole][マネジメントコンソール（AWSの管理画面）][scale=0.8]{
//}

== ドメインのネームサーバをRoute53に変更

それではお名前.comで買ったドメインのネームサーバをRoute53に変更する作業を行いましょう。先ずはRoute53で自分のドメインのゾーンを作成します。筆者はstartdns.funというドメイン名を使いますので、あなたも自分のドメイン名のゾーンを作成してみてください。

=== Route53でホストゾーンを作成

AWSのマネジメントコンソールで、左上の「サービス」を押すとAWSのサービス一覧（@<img>{serviceRoute53}）が表示されます。@<fn>{classmethod}「ネットワーキング ＆ コンテンツ配信」というグループにあるRoute53を選択してください。

//footnote[classmethod][クラスメソッドのDevelopers.IOで2018年時点のAWS全サービスがまとめられているので、AWS全体をざっと俯瞰したい方はそちらがお勧めです。@<href>{https://dev.classmethod.jp/cloud/aws/aws-summary-2018-1/}]

//image[serviceRoute53][サービス一覧からRoute53を選択][scale=0.8]{
//}

Route53を押すといくつかメニューが表示される（@<img>{route53Top}）ので、いちばん左側にあるDNS managementの「Get started now」を押してください。

//image[route53Top][DNS managementの「Get started now」を押す][scale=0.8]{
//}

Route53というネームサーバの中に自分のドメインのゾーンを作りたいので、ホストゾーンの画面（@<img>{hostedZones}）が表示されたら「Create Hosted Zone」を押してください。

//image[hostedZones][「Create Hosted Zone」を押す][scale=0.8]{
//}

まだゾーンがひとつもないため「You have no hosted zones」と表示（@<img>{youHaveNoHostedZones}）されます。再び「Create Hosted Zone」ボタンを押してください。

//image[youHaveNoHostedZones][「You have no hosted zones」と表示されたら再び「Create Hosted Zone」を押す][scale=0.8]{
//}

ホストゾーンの作成画面（@<img>{createHostedZones}）を開いたらDomain Nameのところに先ほどお名前.comで買った自分のドメイン名を書きます。筆者はstartdns.funというドメイン名を買ったので、Domain Nameのところにstartdns.funと書きました。

//image[createHostedZones][お名前.comで買った自分のドメインを書く][scale=0.8]{
//}

TypeはPublic Hosted Zoneを選択（@<table>{hostedZones}）します。「Public Hosted Zone」にしておけば外から「このドメイン名に紐づいてるIPはなに？」と聞かれたときにRoute53のネームサーバが「IPは〇〇だよ」と返事をします。ここを「Private Hosted Zone for Amazon VPC」にしてしまうとAWS内での名前解決しか出来なくなり、外から聞かれても何も答えてくれなくなってしまいますので、必ず「Public Hosted Zone」にしておいてください。入力完了したら「Create」を押します。

//table[hostedZones][ホストゾーン作成時の設定]{
項目	入力するもの
------------------------------------
Domain Name	お名前.comで買った自分のドメイン名
Comment	何も入力しない
Type	Public Hosted Zone
//}

これでRoute53というネームサーバの中に自分のドメイン名のゾーンが出来て、ゾーンの中にドメイン名のネームサーバを示すNSレコードと管理情報を示すSOAレコードというリソースレコードも出来ました。（@<img>{nsRecord}）

//image[nsRecord][自分のドメイン名のゾーンとその中のリソースレコードが出来た][scale=0.8]{
//}

=== 自分のドメイン名のネームサーバが何か確認

ではこれで自分のドメイン名のネームサーバがRoute53になったのか、ちょっと確認してみましょう。

ブラウザの別タブで「dig」を検索（@<img>{searchDig}）して、一番上の「nslookup(dig)テスト【DNSサーバ接続確認】」@<fn>{cmanUrl}というページを開きます。

//footnote[cmanUrl][@<href>{https://www.cman.jp/network/support/nslookup.html}]

//image[searchDig][「dig」で検索][scale=0.8]{
//}

このサイトでは自分のドメイン名のネームサーバが何になっているのか、今の状態を確認できます。では「nslookup(dig)テスト【DNSサーバ接続確認】」のページ（@<img>{digStartDnsFunByCman}）で「ホスト名(FQDN)を指定してください」という欄に自分のドメインを入力（@<table>{digByCman}）して、オプションで「NS：正式なネームサーバ@<fn>{nameServer}」を選択したら「dig実行」を押してください。

//footnote[nameServer][NSレコードはドメイン名のゾーンを管理するネームサーバを示すリソースレコードです。]

//table[digByCman][ネームサーバを調べる際の入力項目]{
項目	入力するもの
------------------------------------
ホスト名(FQDN)を指定してください	お名前.comで買った自分のドメイン名
オプション（任意）	NS：正式なネームサーバ
//}

//image[digStartDnsFunByCman][自分のドメイン名を入力してネームサーバを調べる][scale=0.8]{
//}

ちょっと下にスクロールして確認結果のANSWER SECTIONというところを見てください。次のように表示されましたか？

//cmd{
;; ANSWER SECTION:
startdns.fun.       300 IN NS   dns1.onamae.com.
startdns.fun.       300 IN NS   dns2.onamae.com.
//}

ANSWER SECTIONは名前のとおり「startdns.funのNSレコードは？」という質問に対する答えです。NSレコードはそのドメインのゾーンを管理するネームサーバを示すリソースレコードなので「startdns.funというドメインのゾーンはお名前.comのネームサーバの中にあるよ」という答えが返ってきた、ということです。

先ほどAWSのRoute53というネームサーバの中に自分のドメインのゾーンを作ったのに、なぜかドメインのネームサーバはまだお名前.comのままになっています。これはどういうことなのでしょう？

これはstartdns.funというゾーンがお名前.comのネームサーバに委任されていることで、次のような流れになっているからです。

//image[whichOneIsMyNameServer][ゾーンがお名前.comのネームサーバに委任されている][scale=0.8]{
//}

このようにお名前.comのネームサーバとRoute53のネームサーバ、どちらにもstartdns.funのゾーンがあるのですが、上位ネームサーバのa.nic.funが「startdns.funについてはdns1.onamae.comに委任する」という設定なので、お名前.comのネームサーバがstartdns.funの権威を持った状態になっています。そのためstartdns.funのNSレコードを問い合わせたときに誰もRoute53のネームサーバには聞きに来ないのです。

そもそもお名前.comでドメインを買うと、デフォルトの設定でネームサーバには次の2つが設定されています。

 * dns1.onamae.com.
 * dns2.onamae.com.

そのためネームサーバをRoute53に変更したければ、Route53で自分のドメインのゾーンを用意するだけでなく、さらにお名前.comの管理画面で「ゾーンはお名前.comにある」という設定を「ゾーンはRoute53にある」という設定に書き換えなければいけなかったのです。

先ほどのマネジメントコンソールに戻って（@<img>{nsRecord2}）NSレコードのValueを見てみましょう。次のような4つのネームサーバが表示されていると思います。@<fn>{route53NameServer}この4つは後ほど必要になりますのでパソコンのメモ帳に書き留めておいてください。

 * ns-943.awsdns-53.net.
 * ns-1605.awsdns-08.co.uk.
 * ns-1072.awsdns-06.org.
 * ns-177.awsdns-22.com.

//footnote[route53NameServer][数字やTLDは人によって異なります。あなたのドメインのNSレコードをメモしてください。]

//image[nsRecord2][NSレコードのValueに書かれたネームサーバをメモしておく][scale=0.8]{
//}

=== ネームサーバをお名前.comからRoute53に変更

それでは自分のドメイン名のネームサーバをRoute53に変更する設定を行いましょう。ブラウザの別タブでお名前.comのトップページ@<fn>{onamaeUrl}を開いて右上の「ドメインNavi ログイン」をクリックしてください。（@<img>{onamaeTopPageAgain}）

//footnote[onamaeUrl][@<href>{https://www.onamae.com/}]

//image[onamaeTopPageAgain][右上の「ドメインNavi ログイン」をクリック][scale=0.8]{
//}

ログイン画面（@<img>{domainNaviLogin}）が表示されたら、ドメイン名を買ったときに発行されたお名前ID@<fn>{forgetOnamaeId}とパスワードを入力し、「ログイン」を押して管理画面のドメインNaviにログインします。

//footnote[forgetOnamaeId][もしお名前IDを忘れてしまったら、ドメイン登録したときに届くメールに記載されています。]

//image[domainNaviLogin][お名前IDとパスワードを入れてドメインNaviにログイン][scale=0.8]{
//}

ログインするとドメインNaviのトップページではなく「ドメイン契約更新」の画面（@<img>{continueContract}）が表示されます。@<fn>{abTestAgain}

//footnote[abTestAgain][ABテストの影響でログインするお名前IDによってドメインNaviの見た目が異なるかもしれません。見た目に関わらず管理画面でやりたいことは同じで「ドメインのネームサーバを、デフォルトのお名前.comからRoute53に変更したい」だけです。]

//image[continueContract][ドメインNavi ドメイン契約更新][scale=0.8]{
//}

繰り返しになりますが「ドメイン契約更新」の画面が表示されるのは、ドメインNaviがログインするたびに「来年の更新をしませんか？」と聞いてくる仕様だからです。先ほど買ったドメインの設定変更がしたいので、上部のメニューで左から2つ目の「ドメイン」をクリックしてください。

他のページへ移動しようとすると「更新手続きをお忘れではございませんか？（中略）更新が必要なドメインはお早めにお手続きされることをお勧めいたします。」と警告が出ますが（@<img>{contractRemind}）、前述のとおり有効期限は1年も先です。問題ありませんので「更新画面から移動する」を押してください。

//image[contractRemind][ドメインNavi 更新アラート][scale=0.8]{
//}

ドメイン一覧（@<img>{domainNaviDomainList}）には自分が買ったドメイン名（筆者ならstartdns.fun）があります。買ったばかりのドメイン名はネームサーバが「初期設定」になっているので、そこをクリックして「ネームサーバー設定」の画面に進みます。

//image[domainNaviDomainList][ドメインNavi ドメイン一覧で「初期設定」を押す][scale=0.8]{
//}

ネームサーバー設定の画面（@<img>{nameServerSetting01}）を開いたら、少し下の「2.ネームサーバーの選択」までスクロールしてください。

//image[nameServerSetting01][ドメインNavi ネームサーバー設定][scale=0.8]{
//}

変更前（@<img>{nameServerSetting02}）は「お名前.comのネームサーバー」になっているので「その他のネームサーバー」というラジオボタンを選択（@<img>{nameServerSetting03}）します。「ネームサーバー情報を入力」と書いてあるところに、さきほどメモしたRoute53のネームサーバを1行ずつ書いてください。初めは入力欄が3つしかないですが＋を押すと追加できます。4つとも入力出来たら「確認」を押します。

//image[nameServerSetting02][ネームサーバーの選択 変更前][scale=0.8]{
//}

//image[nameServerSetting03][さきほどメモしたRoute53のネームサーバを4つ書く][scale=0.8]{
//}

「確認」を押すと確認画面（@<img>{confirmNameServerSetting}）が出てくるので、ネームサーバー情報がさきほどメモしたRoute53のネームサーバになっていることを確認して「OK」を押します。

//image[confirmNameServerSetting][ネームサーバの設定確認][scale=0.8]{
//}

「完了しました。」（@<img>{nameServerSettingFinish}）と表示されたらネームサーバの設定変更は完了です。ネームサーバの設定変更が完了すると、少し経ってから「[お名前.com]ネームサーバー情報変更 完了通知」という件名のメールが届きます。

//image[nameServerSettingFinish][ネームサーバの設定変更完了][scale=0.8]{
//}

=== TTLが過ぎるまではネームサーバが切り替わらない

ところで今、ネームサーバをお名前.comからRoute53に変更しましたが、古い設定のTTLが過ぎるまでフルリゾルバにはキャッシュが残っています。

TTLとはTime To Liveの略でキャッシュ保持時間のことです。先ほど「nslookup(dig)テスト【DNSサーバ接続確認】@<fn>{cmanUrl2}」でNSレコードを確認したとき、ANSWER SECTIONに表示されていた「300」というのがTTLの値です。

//footnote[cmanUrl2][@<href>{https://www.cman.jp/network/support/nslookup.html}]

//cmd{
;; ANSWER SECTION:
startdns.fun.       300 IN NS   dns1.onamae.com.
startdns.fun.       300 IN NS   dns2.onamae.com.
//}

TTLに300と書かれているので、最大で300秒＝5分待てばキャッシュの期限が切れてネームサーバはRoute53に切り替わるはずです。再び「nslookup(dig)テスト【DNSサーバ接続確認】」で「ホスト名(FQDN)を指定してください」という欄に自分のドメインを入力（@<img>{digStartDnsFunByCman2}）して、オプションで「NS：正式なネームサーバ」を選択したら「dig実行」を押してください。

//image[digStartDnsFunByCman2][再び自分のドメインのネームサーバを調べる][scale=0.8]{
//}

「dig実行」を押したら、ちょっと下にスクロールして確認結果のANSWER SECTIONというところを見てください。次のように表示されていればネームサーバはちゃんとRoute53へ切り替わっています。数字やTLDは人によって異なるため、先ほどメモしておいたRoute53のネームサーバが表示されていることを確認してください。

//cmd{
;; ANSWER SECTION:
startdns.fun. 3600 IN NS ns-1072.awsdns-06.org.
startdns.fun. 3600 IN NS ns-1605.awsdns-08.co.uk.
startdns.fun. 3600 IN NS ns-177.awsdns-22.com.
startdns.fun. 3600 IN NS ns-943.awsdns-53.net.
//}

よく「DNSを変更したけど浸透には時間がかかる」のように言われますが、これは正確に言えば「TTLに指定された時間が過ぎるまではフルリゾルバに古いリソースレコードのキャッシュが残っているため、ネームサーバにある新しいリソースレコードの情報を取りに行かず、キャッシュの情報が使われてしまう」ということです。人によって異なるフルリゾルバを使っているため、たとえばサイトリニューアルでAレコードを書き換えたときに、Web制作会社のA社は新しいサイトが見られるがクライアントのB社ではまだ古いサイトが表示される、といった現象が起こります。

理屈さえ分かれば、「浸透」というふんわりした言葉を信じて「いつ切り替わるのかなー」と気長に待つ必要はありません。変更前のTTLを把握しておけば、最大でどれだけ待てば新しいリソースレコードの情報に切り替わるのかは分かります。事前にTTLを短くしておくことで反映までにかかる時間を短くすることもできます。いつまでに切り替わるのか正確に分かっていれば、逆にその時間までに切り替わらなかったときにも「何かがおかしいぞ」ときちんと気付くことができます。

逆に当面は書き換える予定がないリソースレコードについては、TTLを長くしておけばフルリゾルバが都度ネームサーバまで聞きに来なくてよいのでキャッシュヒット率が上がりますし、万が一ネームサーバが死んでしまったときもしばらくはキャッシュでしのげるので障害の影響範囲を狭めることができます。

「どうしてもキャッシュを今すぐ消したい！」という場合は、もし情シスが自社のフルリゾルバを管理しているのであれば「フルリゾルバのキャッシュをクリアして！」と頼めばキャッシュがなくなって、改めてネームサーバへリソースレコードを問い合わせに行ってくれます。

===[column] 【コラム】名前解決はプッシュ型じゃなくてプル型

名前解決の仕組みは「エンドユーザからの問い合わせを契機にフルリゾルバがネームサーバへプルしにいく」ものであり、「リソースレコードの追加や変更を契機にネームサーバがフルリゾルバへプッシュしにいく」ものではありません。

MySQLのレプリケーションなどもそうですが、マスターがスレーブにデータをプッシュしにいくのか、スレーブがマスターからデータをプルしてくるのか、つまり「何を契機にどっちが渡しに（もしくは取りに）動くのか？」を理解しておくのは大切なことです。@<fn>{masterSlave}

===[/column]

//footnote[masterSlave][ちなみにMySQLのレプリケーションは、スレーブがマスターからデータをプルします]

=== 使われるのは親と子どちらのNSレコードのTTL？

ちなみに「ネームサーバがいつ切り替わるのかはNSレコードのTTLを見れば分かる」と前述しましたが、実はNSレコードは2箇所にあります。技術書典のウェブサイトで使われている@<code>{techbookfest.org}というドメイン名を例に、あなた自身がフルリゾルバになった気持ちでルートネームサーバから順を追って名前解決の流れをたどっていってみましょう。

先ずはフルリゾルバになりきって、digコマンドでルートネームサーバに「techbookfest.orgのNSレコードを教えて」と話しかけてみましょう。もちろんルートネームサーバ自身は@<code>{techbookfest.org}のNSレコードは知らないので、答え（ANSWER SECTION）は返ってこず、代わりに「@<code>{org}については@<code>{a0.org.afilias-nst.info}（他5つ）というネームサーバに任せているよ」という委任先の情報（AUTHORITY SECTION）が返ってきます。@<fn>{digOption}これが1往復目です。

//footnote[digOption][フルリゾルバになりきって名前解決がしたかったので非再帰的に問い合わせる「+norecurse」というオプションを、そして見やすくするためAUTHORITY SECTIONだけを表示したかったので「+noall +author」というオプションを付けています。またフルリゾルバではなく、ネームサーバに直接問い合わせたかったので@で対象のネームサーバを指定しています]

//cmd{
# dig +norecurse +noall +author techbookfest.org ns @a.root-servers.net
org.                    172800  IN      NS      a0.org.afilias-nst.info.
org.                    172800  IN      NS      a2.org.afilias-nst.info.
org.                    172800  IN      NS      b0.org.afilias-nst.org.
org.                    172800  IN      NS      b2.org.afilias-nst.org.
org.                    172800  IN      NS      c0.org.afilias-nst.info.
org.                    172800  IN      NS      d0.org.afilias-nst.org.
//}

ルートネームサーバから「@<code>{org}については@<code>{a0.org.afilias-nst.info}（他5つ）に任せている」という情報が得られたので、続けて@<code>{a0.org.afilias-nst.info}に「@<code>{techbookfest.org}のNSレコードを教えて」と話しかけてみましょう。するとやはり答え（ANSWER SECTION）は返ってこず、また代わりに「@<code>{techbookfest.org}については@<code>{ns-cloud-b1.googledomains.com}（他3つ）というネームサーバに任せているよ」という委任先の情報（AUTHORITY SECTION）が返ってきました。これが2往復目です。

//cmd{
$ dig +norecurse +noall +author techbookfest.org ns @a0.org.afilias-nst.info
techbookfest.org.       86400   IN      NS      ns-cloud-b1.googledomains.com.
techbookfest.org.       86400   IN      NS      ns-cloud-b4.googledomains.com.
techbookfest.org.       86400   IN      NS      ns-cloud-b2.googledomains.com.
techbookfest.org.       86400   IN      NS      ns-cloud-b3.googledomains.com.
//}

「@<code>{techbookfest.org}については@<code>{ns-cloud-b1.googledomains.com}（他3つ）に任せている」という情報が得られたので、3度目の正直で@<code>{ns-cloud-b1.googledomains.com}に「@<code>{techbookfest.org}のNSレコードを教えて」と話しかけてみましょう。するとようやく答え（ANSWER SECTION）が返ってきました。@<fn>{digOption2}これが3往復目です。

//footnote[digOption2][今度はANSWER SECTIONだけを表示したかったので「+noall +answer」というオプションを付けています]

//cmd{
$ dig +norecurse +noall +answer techbookfest.org ns @ns-cloud-b1.googledomains.com
techbookfest.org.       21600   IN      NS      ns-cloud-b1.googledomains.com.
techbookfest.org.       21600   IN      NS      ns-cloud-b2.googledomains.com.
techbookfest.org.       21600   IN      NS      ns-cloud-b3.googledomains.com.
techbookfest.org.       21600   IN      NS      ns-cloud-b4.googledomains.com.
//}

2往復目と3往復目を並べて比較してみましょう。2往復目の@<code>{org}を任されている@<code>{a0.org.afilias-nst.info}を「親ネームサーバ」、3往復目の@<code>{techbookfest.org}を任されている@<code>{ns-cloud-b1.googledomains.com}を「子ネームサーバ」とした場合、親にも子にもNSレコードがあることが分かります。

//cmd{
$ dig +norecurse +noall +author techbookfest.org ns @a0.org.afilias-nst.info
techbookfest.org.       86400   IN      NS      ns-cloud-b1.googledomains.com.
techbookfest.org.       86400   IN      NS      ns-cloud-b4.googledomains.com.
techbookfest.org.       86400   IN      NS      ns-cloud-b2.googledomains.com.
techbookfest.org.       86400   IN      NS      ns-cloud-b3.googledomains.com.

$ dig +norecurse +noall +answer techbookfest.org ns @ns-cloud-b1.googledomains.com
techbookfest.org.       21600   IN      NS      ns-cloud-b1.googledomains.com.
techbookfest.org.       21600   IN      NS      ns-cloud-b2.googledomains.com.
techbookfest.org.       21600   IN      NS      ns-cloud-b3.googledomains.com.
techbookfest.org.       21600   IN      NS      ns-cloud-b4.googledomains.com.
//}

親と子のNSレコードはどちらも同じ内容ですが、TTLだけが86400秒（1日）と21600秒（6時間）で異なります。このとき、@<code>{techbookfest.org}を任されている、つまり権威（AUTHORITY）を持っているのは子の方なので、フルリゾルバでのキャッシュ保持時間は子のTTLで指定されている6時間になる、と筆者は思っていました。

しかし親切な読者の方から教えていただいたのですが、この挙動はフルリゾルバの実装に依存し、子のTTLに従うフルリゾルバの方が多いものの、OCNのように親のTTLに従うフルリゾルバも一部存在するのだそうです。その場合、フルリゾルバでのキャッシュ保持時間は6時間ではなく、親のTTLで指定されている1日になってしまいます。@<fn>{qiita}

//footnote[qiita][ただしこの件については、筆者が契約しているISPはOCNではなかったため自身で検証ができていません。「親のTTLに従うフルリゾルバも存在するそうだ」という伝聞で申し訳ないのですが、2018年5月に投稿されたこちらのQiitaで紹介されています。 技術書典4で販売された「DNSをはじめよう」をフォローする感じの記事にしたい - Qiita @<href>{https://qiita.com/soushi/items/7432710308a78a684299}]

=== 【ドリル】ネームサーバを変えること≠レジストラを変えること

==== 問題

あなたは今、自分が買ったドメイン名のネームサーバをデフォルト設定のお名前.comから、Route53のネームサーバに変更しました。1年後に「ドメイン名がもうすぐ有効期限を迎えるので更新しましょう！」と連絡してくるのはどちらですか？

 * A. Route53
 * B. お名前.com

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はBです。今行った作業はドメイン名のネームサーバを、デフォルト設定のお名前.comからAWSのRoute53というネームサーバに変更しただけです。レジストラ（ドメインを購入するお店）をお名前.comからRoute53に変更する「レジストラ移管」を行ったわけではないので、1年後に更新確認の連絡をしてくるのもお名前.comです。

Route53のRegistered domainsというメニューからドメイン名を購入することもできますがお名前.comに比べると値段が高いので、Route53のネームサーバを使いたいだけであれば、本著のようにドメイン名はお名前.comで買ってRoute53のネームサーバを使う方がお勧めです。

===[column] 【コラム】DNSの次はAWSをはじめたい？

「DNSをはじめよう」の続編である「AWSをはじめよう」（@<img>{startAWS}）は、AWSの環境で実際にサーバを立て、自分のドメイン名でウェブサイトを作って公開するところまでがっつりやるハンズオン形式の本です。BOOTH@<fn>{howToBuy}で購入できますので、本著を読み終わった後に「折角ドメイン名買ったし、サイトを作るところまでやってみたい！」と思ったら続けてチャレンジしてみてください。

//image[startAWS][再び自分のドメインのネームサーバを調べる][scale=0.6]{
//}


ちなみにBOOTHはピクシブ株式会社@<fn>{pixiv}が運営している同人誌の通販及びダウンロード販売サイトで、書籍版を購入すると1～2営業日以内に本がBOOTH倉庫からネコポスで送られてきます。PDF版なら購入後すぐにダウンロードして読むことができます。技術書典で頒布されている同人誌の多くはBOOTHでも購入できますので、気になる方は「技術書典」のタグで検索@<fn>{techBookFest}してみることをお勧めします。

「AWSをはじめよう」はAmazonのKindleでも販売していますが、そちらはPDFを一度画像に変換しており本文の検索ができないため、BOOTHのPDF版の方がお勧めです。

===[/column]

//footnote[howToBuy][@<href>{https://mochikoastech.booth.pm/}]
//footnote[pixiv][イラストを投稿できるSNS、pixivでお馴染み。@<href>{https://www.pixiv.net/}]
//footnote[techBookFest][@<href>{https://booth.pm/ja/search/技術書典}]
