/*
 * Copyright 2020 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file    oes_packets.h
 *
 * 订单执行系统订单接收模块通讯报文定义
 *
 * @version 0.11.1      2016/11/17
 * @version 0.12        2016/11/30
 *          - 在登录报文中增加协议版本号信息, 并在登录时校验协议版本号的兼容性
 * @version 0.12.3      2017/01/10
 *          - 新增期权持仓查询的消息类型
 *          - 调整查询类消息类型的取值定义
 * @version 0.12.6.2    2017/03/16
 *          - 重命名 ‘出入金委托’ 消息 OESMSG_NONTRD_CASH_TRSF_REQ =>
 * OESMSG_NONTRD_FUND_TRSF_REQ
 *          - 新增 ‘出入金委托响应-业务拒绝’、‘出入金委托执行报告’ 两类回报消息
 *          - 删除 ‘出入金管理登录消息’ 宏定义
 *          - 重命名 ‘出入金委托’消息的结构体定义 OesCashTrsfReqT =>
 * OesFundTrsfReqT
 * @version 0.15.2      2017/07/18
 *          - 新增 查询新股配号、中签信息消息类型定义(OESMSG_QRYMSG_LOT_WINNING)
 * @version 0.15.2.1    2017/07/31
 *          - 出入金业务拒绝消息类型变更 OesFundTrsfReqT => OesFundTrsfRejectT
 *          - 出入金委托回报的结构体(OesFundTrsfReportT) 中新增字段 '错误码信息
 * (rejReasonInfo)'
 * @version 0.15.4      2017/09/04
 *          - 新增交易类请求消息 '撤单请求消息 (OESMSG_ORD_CANCEL_REQUEST)'
 *          - 新增结构体 '撤单请求 (OesOrdCancelReqT)'
 *          - 新增回报消息类型 '撤单拒绝 (OESMSG_RPT_CANCEL_REJECT)'
 *              - 对应回报消息 OesRptMsgBodyT.cancelRejectRsp
 *          - 委托拒绝消息中将不再包含撤单委托,
 * 所有被OES拒绝的撤单请求和撤单委托都将通过新增的撤单拒绝消息进行回报
 *          - 新增回报消息类型 '资金变动信息 (OESMSG_RPT_CASH_ASSET_VARIATION)'
 *              - 对应回报消息 OesRptMsgBodyT.cashAssetRpt
 *          - 新增回报消息类型 '持仓变动信息 (股票)
 * (OESMSG_RPT_STOCK_HOLDING_VARIATION)'
 *              - 对应回报消息 OesRptMsgBodyT.stkHoldingRpt
 *          - 新增回报消息类型 '持仓变动信息 (期权)
 * (OESMSG_RPT_OPTION_HOLDING_VARIATION)'
 *              - 对应回报消息 OesRptMsgBodyT.optHoldingRpt
 * @version 0.15.4.1    2017/09/07
 *          - 调整回报消息类型的定义顺序和取值
 *              - OESMSG_RPT_ORDER_INSERT, OESMSG_RPT_ORDER_REJECT,
 * OESMSG_RPT_CANCEL_REJECT
 *          - 登录应答报文(OesLogonRspT) 中增加字段 客户端环境号(clEnvId)
 * @version 0.15.4.2    2017/10/16
 *          - 新增交易类请求消息 '测试请求 (OesTestRequestReqT)'
 *          - 新增回报消息类型 '测试请求的应答 (OesTestRequestRspT)'
 * @version 0.15.5      2017/11/03
 *          - 删除回报消息类型 '撤单拒绝 (OESMSG_RPT_CANCEL_REJECT)', 并整合到
 * '委托拒绝 (OESMSG_RPT_ORDER_REJECT)' 消息中
 *          - 重命名回报消息类型 OESMSG_RPT_ORDER_REJECT =>
 * OESMSG_RPT_BUSINESS_REJECT (OES业务拒绝, 委托/撤单未通过风控检查等)
 *          - 增加可订阅的回报消息类型 OES_SUB_RPT_TYPE_BUSINESS_REJECT
 *          - 当前采用的协议版本号(OES_APPL_VER_ID) 升级到 0.15.5
 *          - 兼容最低的协议版本号(OES_MIN_APPL_VER_ID) 升级到 0.15.5
 * @version 0.15.5.1    2017/11/15
 *          - 增加数值类型的协议版本号 OES_APPL_VER_VALUE, 以方便比对版本
 * @version 0.15.6      2018/03/28
 *          - 增加修改密码请求/应答报文和消息代码定义
 *          - 增加批量委托请求报文和消息代码定义
 *          - 登录请求报文(OesLogonReqT) 中增加字段
 * 客户端设备序列号(clientDriverId)
 *          - 增加默认回报消息类型 OES_SUB_RPT_TYPE_DEFAULT
 *          - 新增回报消息类型 '市场状态信息 (OESMSG_RPT_MARKET_STATE)'
 *              - 对应回报消息 OesRspMsgBodyT.mktStateRpt
 *          - 回报消息头(OesRptMsgHeadT) 中增加字段 执行类型(execType),
 * 用以区分回报的执行类型(参考eOesExecTypeT定义）
 * @version 0.15.5.13   2018/07/20
 *          - 登录应答报文(OesLogonRspT) 中增加字段:
 *              - 客户端类型 (clientType)
 *              - 客户端状态 (clientStatus)
 * @version 0.15.5.16   2018/08/31
 *          - 登录应答报文(OesLogonRspT) 中增加字段:
 *              - 客户端类型(clientType)
 *              - 客户端状态(clientStatus)
 *          - 新增 查询客户端总览信息(OESMSG_QRYMSG_CLIENT_OVERVIEW)
 * 消息类型定义
 *          - 新增 查询客户主柜资金信息(OESMSG_QRYMSG_COUNTER_CASH) 消息类型定义
 * @version 0.15.5.17   2018/11/23
 *          - 登录应答报文(OesLogonRspT) 中增加字段:
 *              - 服务端集群号(setNum)
 * @version 0.15.7.6    2018/11/03
 *          - 新增
 * OES服务状态回报消息类型(OESMSG_RPT_SERVICE_STATE)，暂不支持订阅推送
 * @version 0.15.9      2018/03/12
 *          - 为了支持科创板, 新增以下查询消息类型 (兼容之前版本的API)
 *              - 查询证券账户信息 (OESMSG_QRYMSG_INV_ACCT)
 *              - 查询现货产品信息 (OESMSG_QRYMSG_STOCK)
 * @version 0.15.10.6   2020/04/19
 *          - 将延迟统计相关的时间戳字段升级为纳秒级时间戳 (内部使用的字段,
 * 协议保持兼容, STimeval32T => STimespec32T)
 * @version 0.15.11     2020/05/29
 *          - 为了支持创业板, 新增以下查询消息类型 (兼容之前版本的API)
 *              - 查询证券发行信息 (OESMSG_QRYMSG_ISSUE)
 *              - 查询现货产品信息 (OESMSG_QRYMSG_STOCK)
 *              - 查询ETF成份证券信息 (OESMSG_QRYMSG_ETF_COMPONENT)
 * @version 0.16        2019/11/20
 *          - 新增回报消息类型 '通知消息回报 (OESMSG_RPT_NOTIFY_INFO)'
 *              - 对应回报消息 OesRptMsgBodyT.notifyInfoRpt
 *          - 新增 查询通知消息(OESMSG_QRYMSG_NOTIFY_INFO) 消息类型定义
 *          - 新增回报消息类型 '期权标的持仓变动信息
 * (OESMSG_RPT_OPTION_UNDERLYING_HOLDING_VARIATION)'
 *              - 对应回报消息 OesRptMsgBodyT.optUnderlyingHoldingRpt
 *          - 新增回报消息类型 '期权账户结算单确认
 * (OESMSG_RPT_OPTION_SETTLEMENT_CONFIRMED)'
 *              - 对应回报消息 OesRptMsgBodyT.optSettlementConfirmRpt
 *          - 新增 查询期权标的持仓信息(OESMSG_QRYMSG_OPT_UNDERLYING_HLD)
 * 消息类型定义
 *          - 新增 查询期权限仓额度信息(OESMSG_QRYMSG_OPT_POSITION_LIMIT)
 * 消息类型定义
 *          - 新增 查询期权行权指派信息(OESMSG_QRYMSG_OPT_EXERCISE_ASSIGN)
 * 消息类型定义
 *          - 新增以下查询消息类型 (兼容之前版本的API)
 *              - 查询委托信息 (OESMSG_QRYMSG_ORD)
 *              - 查询成交信息 (OESMSG_QRYMSG_TRD)
 *              - 查询客户资金信息 (OESMSG_QRYMSG_CASH_ASSET)
 *          - 重命名 ‘资金变动回报信息’消息的结构体定义 OesCashAssetItemT =>
 * OesCashAssetReportT
 *              - 对应回报消息 OesRptMsgBodyT.cashAssetRpt
 *          - 重命名 ‘持仓变动回报信息 (股票)’消息的结构体定义
 * OesStkHoldingItemT => OesStkHoldingReportT
 *              - 对应回报消息 OesRptMsgBodyT.stkHoldingRpt
 *          - 重命名 ‘持仓变动回报信息 (期权)’消息的结构体定义
 * OesOptHoldingItemT => OesOptHoldingReportT
 *              - 对应回报消息 OesRptMsgBodyT.optHoldingRpt
 * @version 0.16.0.2    2020/01/03
 *          - '券商参数信息 (OesBrokerParamsInfoT)' 中
 *              - 新增 服务端业务范围 (businessScope) 字段
 *              - 新增 期权扩展参数 (optionExt) 结构, 其中新增 投资人出金提取线
 * (withdrawLineRatio) 字段
 * @version 0.16.0.3    2020/01/14
 *          - 为了兼容之前版本的API, 新增以下查询消息类型
 *              - 查询期权行权指派信息 (OESMSG_QRYMSG_OPT_EXERCISE_ASSIGN)
 * @version 0.17.0.8    2020/04/20
 *          - 调整非交易类消息的消息代码取值
 *          - 新增回报消息类型
 * 融资融券直接还款委托执行报告(OESMSG_RPT_CREDIT_CASH_REPAY_REPORT)
 *              - 对应回报订阅类型 OES_SUB_RPT_TYPE_CREDIT_CASH_REPAY_REPORT
 *              - 对应回报消息 OesRptMsgBodyT.crdDebtCashRepayRpt
 *          - 新增回报消息类型
 * 融资融券合约变动信息(OESMSG_RPT_CREDIT_DEBT_CONTRACT_VARIATION)
 *              - 对应回报订阅类型
 * OES_SUB_RPT_TYPE_CREDIT_DEBT_CONTRACT_VARIATION
 *              - 对应回报消息 OesRptMsgBodyT.crdDebtContractRpt
 *          - 新增回报消息类型
 * 融资融券合约流水信息(OESMSG_RPT_CREDIT_DEBT_JOURNAL)
 *              - 对应回报订阅类型 OES_SUB_RPT_TYPE_CREDIT_DEBT_JOURNAL
 *              - 对应回报消息 OesRptMsgBodyT.crdDebtJournalRpt
 * @version 0.17.1      2020/06/16
 *          - 新增 查询融资融券业务可取资金(OESMSG_QRYMSG_CRD_DRAWABLE_BALANCE)
 * 消息类型定义
 *          - 新增
 * 查询融资融券担保品可转出的最大数量信息(OESMSG_QRYMSG_CRD_COLLATERAL_TRANSFER_OUT_MAX_QTY)
 * 消息类型定义
 *
 * @since   2015/07/30
 */

#ifndef _OES_PACKETS_H
#define _OES_PACKETS_H

#include <oes_global/oes_base_model.h>
#include <oes_global/oes_base_model_credit.h>
#include <oes_global/oes_base_model_option.h>
#include <oes_global/oes_qry_packets.h>
#include <oes_global/oes_qry_packets_credit.h>
#include <oes_global/oes_qry_packets_option.h>
#include <sutil/net/spk_global_packet.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ===================================================================
 * 协议版本号定义
 * =================================================================== */

/** 当前采用的协议版本号 */
#define OES_APPL_VER_ID "0.17.5.8"

/**
 * 当前采用的协议版本号数值
 * - 版本号数值的格式为 10 位整型数值, 形如: 1AABBCCDDX, 其中:
 *   - AA 为主版本号
 *   - BB 为副版本号
 *   - CC 为发布号
 *   - DD 为构建号
 *   - X  0, 表示不带时间戳的正常版本; 1, 表示带时间戳的延迟测量版本
 */
#define OES_APPL_VER_VALUE 1001705081

/** 兼容的最低协议版本号 */
#define OES_MIN_APPL_VER_ID "0.15.5"

/** 应用名称 */
#define OES_APPL_NAME "OES"
/* -------------------------           */

/* ===================================================================
 * 消息代码及报文中的枚举类型定义
 * =================================================================== */

/**
 * 通信消息的消息类型定义
 */
typedef enum _eOesMsgType {
  /*
   * 交易类消息
   */
  OESMSG_ORD_NEW_ORDER = 0x01,      /**< 0x01/01  委托申报消息 */
  OESMSG_ORD_CANCEL_REQUEST = 0x02, /**< 0x02/02  撤单请求消息 */
  OESMSG_ORD_BATCH_ORDERS = 0x03,   /**< 0x03/03  批量委托消息 */

  OESMSG_ORD_CREDIT_REPAY = 0x04,      /**< 0x04/04  融资融券负债归还请求消息 */
  OESMSG_ORD_CREDIT_CASH_REPAY = 0x05, /**< 0x05/05  融资融券直接还款请求消息 */
  __OESMSG_ORD_MAX,                    /**< 最大的委托消息类型 */

  /*
   * 非交易类消息
   */
  __OESMSG_NONTRD_MIN = 0xC0,           /**< 0xC0/192 最小的非交易消息类型 */
  OESMSG_NONTRD_FUND_TRSF_REQ = 0xC1,   /**< 0xC1/193 出入金委托 */
  OESMSG_NONTRD_CHANGE_PASSWORD = 0xC2, /**< 0xC2/194 修改客户端登录密码 */
  OESMSG_NONTRD_OPT_CONFIRM_SETTLEMENT =
      0xC3,            /**< 0xC3/195 期权账户结算单确认 */
  __OESMSG_NONTRD_MAX, /**< 最大的非交易消息类型 */

  /*
   * 执行报告类消息
   */
  __OESMSG_RPT_MIN = 0x0A, /**< 0x0A/10  最小的执行报告消息类型 */
  OESMSG_RPT_SERVICE_STATE =
      0x0E, /**< 0x0E/15  OES服务状态信息 (暂不支持订阅推送) */
  OESMSG_RPT_MARKET_STATE = 0x10,           /**< 0x10/16  市场状态信息 */
  OESMSG_RPT_REPORT_SYNCHRONIZATION = 0x11, /**< 0x11/17  回报同步的应答消息 */

  OESMSG_RPT_BUSINESS_REJECT =
      0x12, /**< 0x12/18  OES业务拒绝 (因未通过风控检查等原因而被OES拒绝) */
  OESMSG_RPT_ORDER_INSERT =
      0x13, /**< 0x13/19  OES委托已生成 (已通过风控检查) */
  OESMSG_RPT_ORDER_REPORT =
      0x14,                       /**< 0x14/20  交易所委托回报
                                     (包括交易所委托拒绝、委托确认和撤单完成通知) */
  OESMSG_RPT_TRADE_REPORT = 0x15, /**< 0x15/21  交易所成交回报 */

  OESMSG_RPT_FUND_TRSF_REJECT = 0x16, /**< 0x16/22  出入金委托拒绝 */
  OESMSG_RPT_FUND_TRSF_REPORT = 0x17, /**< 0x17/23  出入金委托执行报告 */

  OESMSG_RPT_CASH_ASSET_VARIATION = 0x18, /**< 0x18/24  资金变动信息 */
  OESMSG_RPT_STOCK_HOLDING_VARIATION =
      0x19, /**< 0x19/25  持仓变动信息 (股票) */
  OESMSG_RPT_OPTION_HOLDING_VARIATION =
      0x1A, /**< 0x1A/26  持仓变动信息 (期权) */
  OESMSG_RPT_OPTION_UNDERLYING_HOLDING_VARIATION =
      0x1B, /**< 0x1B/27  期权标的持仓变动信息 */
  OESMSG_RPT_OPTION_SETTLEMENT_CONFIRMED =
      0x1C,                      /**< 0x1C/28  期权账户结算单确认消息 */
  OESMSG_RPT_NOTIFY_INFO = 0x1E, /**< 0x1E/30  OES通知消息 */
  OESMSG_RPT_CREDIT_CASH_REPAY_REPORT =
      0x20, /**< 0x20/32  融资融券直接还款委托执行报告 */
  OESMSG_RPT_CREDIT_DEBT_CONTRACT_VARIATION =
      0x21,                              /**< 0x21/33  融资融券合约变动信息 */
  OESMSG_RPT_CREDIT_DEBT_JOURNAL = 0x22, /**< 0x22/34  融资融券合约流水信息 */
  __OESMSG_RPT_MAX,                      /**< 最大的回报消息类型 */

  /*
   * 查询类消息
   */
  __OESMSG_QRYMSG_MIN = 0x2F,           /**< 0x2F/47  最小的查询消息类型 */
  OESMSG_QRYMSG_OPT_HLD = 0x35,         /**< 0x35/53  查询期权持仓信息 */
  OESMSG_QRYMSG_CUST = 0x36,            /**< 0x36/54  查询客户信息 */
  OESMSG_QRYMSG_COMMISSION_RATE = 0x38, /**< 0x38/56  查询客户佣金信息 */
  OESMSG_QRYMSG_FUND_TRSF = 0x39,       /**< 0x39/57  查询出入金信息 */
  OESMSG_QRYMSG_ETF = 0x3B,             /**< 0x3B/59  查询ETF申赎产品信息 */
  OESMSG_QRYMSG_OPTION = 0x3D,          /**< 0x3D/61  查询期权产品信息 */
  OESMSG_QRYMSG_LOT_WINNING = 0x3F,     /**< 0x3F/63  查询新股配号、中签信息 */
  OESMSG_QRYMSG_TRADING_DAY = 0x40,     /**< 0x40/64  查询当前交易日 */
  OESMSG_QRYMSG_MARKET_STATE = 0x41,    /**< 0x41/65  查询市场状态 */
  OESMSG_QRYMSG_COUNTER_CASH = 0x42,    /**< 0x42/66  查询客户主柜资金信息 */
  OESMSG_QRYMSG_OPT_UNDERLYING_HLD = 0x43, /**< 0x43/67  查询期权标的持仓信息 */
  OESMSG_QRYMSG_NOTIFY_INFO = 0x44,        /**< 0x44/68  查询通知消息 */
  OESMSG_QRYMSG_OPT_POSITION_LIMIT = 0x45, /**< 0x45/69  查询期权限仓额度信息 */
  OESMSG_QRYMSG_OPT_PURCHASE_LIMIT = 0x46, /**< 0x46/70  查询期权限购额度信息 */
  OESMSG_QRYMSG_BROKER_PARAMS = 0x48,      /**< 0x48/72  查询券商参数信息 */
  OESMSG_QRYMSG_COLOCATION_PEER_CASH =
      0x49, /**< 0x49/73  查询两地交易时对端结点的资金资产信息 */

  OESMSG_QRYMSG_INV_ACCT =
      0x51, /**< 0x51/81  查询证券账户信息 (0x37的更新版本, @since 0.15.9) */
  OESMSG_QRYMSG_ORD =
      0x54, /**< 0x54/84  查询委托信息 (0x31的更新版本, @since 0.16) */
  OESMSG_QRYMSG_TRD =
      0x55, /**< 0x55/85  查询成交信息 (0x32的更新版本, @since 0.16) */
  OESMSG_QRYMSG_OPT_EXERCISE_ASSIGN =
      0x56, /**< 0x56/86  查询期权行权指派信息 (0x47的更新版本, @since 0.16.0.3)
             */
  OESMSG_QRYMSG_ISSUE =
      0x57, /**< 0x57/87  查询证券发行信息 (0x3E的更新版本, @since 0.15.11) */
  OESMSG_QRYMSG_STOCK =
      0x58, /**< 0x58/88  查询现货产品信息 (0x52的更新版本, @since 0.15.11) */
  OESMSG_QRYMSG_ETF_COMPONENT = 0x59, /**< 0x59/89  查询ETF成份证券信息
                                         (0x3C的更新版本, @since 0.15.11) */
  OESMSG_QRYMSG_CLIENT_OVERVIEW =
      0x5A, /**< 0x5A/90  查询客户端总览信息 (0x30的更新版本, @since 0.15.11.11)
             */
  OESMSG_QRYMSG_CASH_ASSET =
      0x5B, /**< 0x5B/91  查询客户资金信息 (0x53的更新版本, @since 0.17) */
  OESMSG_QRYMSG_STK_HLD =
      0x5C, /**< 0x5C/92  查询股票持仓信息 (0x34的更新版本, @since 0.17) */

  OESMSG_QRYMSG_CRD_DEBT_CONTRACT = 0x80, /**< 0x80/128 查询融资融券合约信息 */
  OESMSG_QRYMSG_CRD_CUST_SECU_DEBT_STATS =
      0x81, /**< 0x81/129 查询客户单证券融资融券负债统计信息 */
  OESMSG_QRYMSG_CRD_CREDIT_ASSET = 0x82, /**< 0x82/130 查询信用资产信息 */
  OESMSG_QRYMSG_CRD_CASH_REPAY_INFO =
      0x83, /**< 0x83/131 查询融资融券业务直接还款信息 */
  OESMSG_QRYMSG_CRD_CASH_POSITION =
      0x84, /**< 0x84/132 查询融资融券业务资金头寸信息 (可融资头寸信息) */
  OESMSG_QRYMSG_CRD_SECURITY_POSITION =
      0x85, /**< 0x85/133 查询融资融券业务证券头寸信息 (可融券头寸信息) */
  OESMSG_QRYMSG_CRD_EXCESS_STOCK =
      0x86, /**< 0x86/134 查询融资融券业务余券信息 */
  OESMSG_QRYMSG_CRD_DEBT_JOURNAL =
      0x87, /**< 0x87/135 查询融资融券合约流水信息 (仅当日流水) */
  OESMSG_QRYMSG_CRD_INTEREST_RATE = 0x88, /**< 0x88/136 查询融资融券息费利率 */
  OESMSG_QRYMSG_CRD_UNDERLYING_INFO =
      0x89, /**< 0x89/137 查询融资融券可充抵保证金证券及融资融券标的信息 */
  OESMSG_QRYMSG_CRD_DRAWABLE_BALANCE =
      0x90, /**< 0x90/138 查询融资融券业务可取资金 */
  OESMSG_QRYMSG_CRD_COLLATERAL_TRANSFER_OUT_MAX_QTY =
      0x91,            /**< 0x91/139 查询融资融券担保品可转出的最大数量 */
  __OESMSG_QRYMSG_MAX, /**< 最大的查询消息类型 */

  /*
   * 公共的会话类消息
   */
  OESMSG_SESS_HEARTBEAT = 0xFA,    /**< 0xFA/250 心跳消息 */
  OESMSG_SESS_TEST_REQUEST = 0xFB, /**< 0xFB/251 测试请求消息 */
  OESMSG_SESS_LOGIN_EXTEND = 0xFC, /**< 0xFC/252 登录扩展消息 */
  OESMSG_SESS_LOGOUT = 0xFE,       /**< 0xFE/254 登出消息 */

  /*
   * 以下消息类型定义已废弃, 只是为了兼容之前的版本而暂时保留
   */
  OESMSG_RPT_ORDER_REJECT = OESMSG_RPT_BUSINESS_REJECT

} eOesMsgTypeT;
/* -------------------------           */

/**
 * 可订阅的回报消息类型定义
 * - 0:      默认回报 (等价于: 0x01,0x02,0x04,0x08,0x10,0x20,0x40)
 * - 0x0001: OES业务拒绝 (未通过风控检查等)
 * - 0x0002: OES委托已生成 (已通过风控检查)
 * - 0x0004: 交易所委托回报 (包括交易所委托拒绝、委托确认和撤单完成通知)
 * - 0x0008: 交易所成交回报
 * - 0x0010: 出入金委托执行报告 (包括出入金委托拒绝、出入金委托回报)
 * - 0x0020: 资金变动信息
 * - 0x0040: 持仓变动信息
 * - 0x0080: 市场状态信息
 * - 0x0100: 通知消息回报
 * - 0x0200: 结算单确认消息
 * - 0x0400: 融资融券直接还款委托执行报告
 * - 0x0800: 融资融券合约变动信息
 * - 0x1000: 融资融券合约流水信息
 * - 0xFFFF: 所有回报
 */
typedef enum _eOesSubscribeReportType {
  /** 默认回报 */
  OES_SUB_RPT_TYPE_DEFAULT = 0,

  /** OES业务拒绝 (未通过风控检查等) */
  OES_SUB_RPT_TYPE_BUSINESS_REJECT = 0x01,

  /** OES委托已生成 (已通过风控检查) */
  OES_SUB_RPT_TYPE_ORDER_INSERT = 0x02,

  /** 交易所委托回报 (包括交易所委托拒绝、委托确认和撤单完成通知) */
  OES_SUB_RPT_TYPE_ORDER_REPORT = 0x04,

  /** 交易所成交回报 */
  OES_SUB_RPT_TYPE_TRADE_REPORT = 0x08,

  /** 出入金委托执行报告 (包括出入金委托拒绝、出入金委托回报) */
  OES_SUB_RPT_TYPE_FUND_TRSF_REPORT = 0x10,

  /** 资金变动信息 */
  OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION = 0x20,

  /** 持仓变动信息 */
  OES_SUB_RPT_TYPE_HOLDING_VARIATION = 0x40,

  /** 市场状态信息 */
  OES_SUB_RPT_TYPE_MARKET_STATE = 0x80,

  /** 通知消息 */
  OES_SUB_RPT_TYPE_NOTIFY_INFO = 0x100,

  /** 结算单确认消息 */
  OES_SUB_RPT_TYPE_SETTLEMETN_CONFIRMED = 0x200,

  /** 融资融券直接还款委托执行报告 */
  OES_SUB_RPT_TYPE_CREDIT_CASH_REPAY_REPORT = 0x400,

  /** 融资融券合约变动信息 */
  OES_SUB_RPT_TYPE_CREDIT_DEBT_CONTRACT_VARIATION = 0x800,

  /** 融资融券合约流水信息 */
  OES_SUB_RPT_TYPE_CREDIT_DEBT_JOURNAL = 0x1000,

  /** 所有回报 */
  OES_SUB_RPT_TYPE_ALL = 0xFFFF,

  __MAX_OES_SUB_RPT_TYPE = 0x7FFFFFFF
} eOesSubscribeReportTypeT;
/* -------------------------           */

/* ===================================================================
 * 会话消息报文定义
 * =================================================================== */

/**
 * 回报同步请求消息
 */
typedef struct _OesReportSynchronizationReq {
  /**
   * 客户端最后接收到的回报数据的回报编号
   * - 等于0, 从头开始推送回报数据
   * - 大于0, 从指定的回报编号开始推送回报数据
   * - 小于0, 从最新的数据开始推送回报数据
   */
  int64 lastRptSeqNum;

  /**
   * 待订阅的客户端环境号
   * - 大于0, 区分环境号, 仅订阅环境号对应的回报数据
   * - 小于等于0, 不区分环境号, 订阅该客户下的所有回报数据
   */
  int8 subscribeEnvId;

  /** 按64位对齐的填充域 */
  uint8 __filler[3];

  /**
   * 待订阅的回报消息种类
   * - 0:      默认回报 (等价于: 0x01,0x02,0x04,0x08,0x10,0x20,0x40)
   * - 0x0001: OES业务拒绝 (未通过风控检查等)
   * - 0x0002: OES委托已生成 (已通过风控检查)
   * - 0x0004: 交易所委托回报 (包括交易所委托拒绝、委托确认和撤单完成通知)
   * - 0x0008: 交易所成交回报
   * - 0x0010: 出入金委托执行报告 (包括出入金委托拒绝、出入金委托回报)
   * - 0x0020: 资金变动信息
   * - 0x0040: 持仓变动信息
   * - 0x0080: 市场状态信息
   * - 0x0100: 通知消息回报
   * - 0xFFFF: 所有回报
   *
   * @see eOesSubscribeReportTypeT
   */
  int32 subscribeRptTypes;
} OesReportSynchronizationReqT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_REPORT_SYNCHRONIZATION_REQ 0, 0, {0}, 0
/* -------------------------           */

/**
 * 回报同步应答消息
 */
typedef struct _OesReportSynchronizationRsp {
  /** 服务端最后已发送或已忽略的回报数据的回报编号 */
  int64 lastRptSeqNum;

  /**
   * 待订阅的客户端环境号
   * - 大于0, 区分环境号, 仅订阅环境号对应的回报数据
   * - 小于等于0, 不区分环境号, 订阅该客户下的所有回报数据
   */
  int8 subscribeEnvId;

  /** 按64位对齐的填充域 */
  uint8 __filler[3];

  /** 已订阅的回报消息种类 */
  int32 subscribeRptTypes;
} OesReportSynchronizationRspT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_REPORT_SYNCHRONIZATION_RSP 0, 0, {0}, 0
/* -------------------------           */

/**
 * 测试请求报文
 */
typedef struct _OesTestRequestReq {
  /** 测试请求标识符 */
  char testReqId[OES_MAX_TEST_REQ_ID_LEN];

  /** 发送时间 (timeval结构或形如'YYYYMMDD-HH:mm:SS.sss'的字符串) */
  char sendTime[OES_MAX_SENDING_TIME_LEN];

  /** 按64位对齐的填充域 */
  char __filler[2];
} OesTestRequestReqT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_TEST_REQUEST_REQ {0}, {0}, {0}
/* -------------------------           */

/**
 * 测试请求的应答报文
 */
typedef struct _OesTestRequestRsp {
  /** 测试请求标识符 */
  char testReqId[OES_MAX_TEST_REQ_ID_LEN];

  /** 测试请求的原始发送时间 (timeval结构或形如'YYYYMMDD-HH:mm:SS.sss'的字符串)
   */
  char origSendTime[OES_MAX_SENDING_TIME_LEN];

  /** 按64位对齐的填充域 */
  char __filler1[2];

  /** 测试请求应答的发送时间 (timeval结构或形如'YYYYMMDD-HH:mm:SS.sss'的字符串)
   */
  char respTime[OES_MAX_SENDING_TIME_LEN];

  /** 按64位对齐的填充域 */
  char __filler2[2];

#ifdef _OES_EXPORT_LATENCY_STATS
  /** 消息实际接收时间 (开始解码等处理之前的时间) */
  STimespec32T __recvTime;
  /** 消息采集处理完成时间 */
  STimespec32T __collectedTime;
  /** 消息推送时间 (写入推送缓存以后, 实际网络发送之前) */
  STimespec32T __pushingTime;
#endif

} OesTestRequestRspT;

/* 结构体初始化值的尾部填充字段定义 */
#ifdef _OES_EXPORT_LATENCY_STATS
#define __NULLOBJ_OES_TEST_REQUEST_RSP_TAILER , {0, 0}, {0, 0}, {0, 0}
#else
#define __NULLOBJ_OES_TEST_REQUEST_RSP_TAILER
#endif

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_TEST_REQUEST_RSP                                           \
  {0}, {0}, {0}, {0}, {0} __NULLOBJ_OES_TEST_REQUEST_RSP_TAILER
/* -------------------------           */

/* ===================================================================
 * 请求消息报文定义
 * =================================================================== */

/**
 * 批量委托请求的消息头
 */
typedef struct _OesBatchOrdersHead {
  /** 本批次的委托请求数量 */
  int32 itemCount;
  /** 按64位对齐的填充域 */
  int32 __filler;
} OesBatchOrdersHeadT;

/**
 * 批量委托请求的完整请求报文
 * (只有请求报文, 没有独立的应答报文)
 */
typedef struct _OesBatchOrdersReq {
  /** 批量委托请求的批次消息头 */
  OesBatchOrdersHeadT batchHead;

  /** 委托请求列表 */
  OesOrdReqT items[1];
} OesBatchOrdersReqT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_BATCH_ORDERS_HEAD 0, 0

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_BATCH_ORDERS_REQ                                           \
  {NULLOBJ_OES_BATCH_ORDERS_HEAD}, {                                           \
    {                                                                          \
      NULLOBJ_OES_ORD_REQ                                                      \
    }                                                                          \
  }
/* -------------------------           */

/**
 * 修改密码请求报文
 */
typedef struct _OesChangePasswordReq {
  /** 加密方法 */
  int32 encryptMethod;
  /** 按64位对齐的填充域 */
  int32 __filler;

  /** 登录用户名 */
  char username[OES_CLIENT_NAME_MAX_LEN];
  /** 用户私有信息 (由客户端自定义填充, 并在回报数据中原样返回) */
  union {
    uint64 u64;    /**< uint64 类型的用户私有信息 */
    int64 i64;     /**< int64 类型的用户私有信息 */
    uint32 u32[2]; /**< uint32[2] 类型的用户私有信息 */
    int32 i32[2];  /**< int32[2] 类型的用户私有信息 */
    char c8[8];    /**< char[8] 类型的用户私有信息 */
  } userInfo;

  /** 之前的登录密码 */
  char oldPassword[OES_PWD_MAX_LEN];
  /** 新的登录密码 */
  char newPassword[OES_PWD_MAX_LEN];
} OesChangePasswordReqT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CHANGE_PASSWORD_REQ 0, 0, {0}, {0}, {0}, {0}
/* -------------------------           */

/**
 * 修改密码应答报文
 */
typedef struct _OesChangePasswordRsp {
  /** 加密方法 */
  int32 encryptMethod;
  /** 按64位对齐的填充域 */
  int32 __filler;

  /** 登录用户名 */
  char username[OES_CLIENT_NAME_MAX_LEN];
  /** 用户私有信息 (由客户端自定义填充, 并在应答数据中原样返回) */
  union {
    uint64 u64;    /**< uint64 类型的用户私有信息 */
    int64 i64;     /**< int64 类型的用户私有信息 */
    uint32 u32[2]; /**< uint32[2] 类型的用户私有信息 */
    int32 i32[2];  /**< int32[2] 类型的用户私有信息 */
    char c8[8];    /**< char[8] 类型的用户私有信息 */
  } userInfo;

  /** 客户端编号 */
  int16 clientId;
  /** 客户端环境号 */
  int8 clEnvId;
  /** 按64位对齐的填充域 */
  int8 __filler2;

  /** 发生日期 (格式为 YYYYMMDD, 形如 20160830) */
  int32 transDate;
  /** 发生时间 (格式为 HHMMSSsss, 形如 141205000) */
  int32 transTime;
  /** 拒绝原因 */
  int32 rejReason;
} OesChangePasswordRspT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_CHANGE_PASSWORD_RSP 0, 0, {0}, {0}, 0, 0, 0, 0, 0, 0
/* -------------------------           */

/**
 * 期权账户结算单确认请求报文
 */
typedef struct _OesOptSettlementConfirmReq {
  /** 客户代码 */
  char custId[OES_CUST_ID_MAX_LEN];

  /** 用户私有信息 (由客户端自定义填充, 并在回报数据中原样返回) */
  union {
    uint64 u64;    /**< uint64 类型的用户私有信息 */
    int64 i64;     /**< int64 类型的用户私有信息 */
    uint32 u32[2]; /**< uint32[2] 类型的用户私有信息 */
    int32 i32[2];  /**< int32[2] 类型的用户私有信息 */
    char c8[8];    /**< char[8] 类型的用户私有信息 */
  } userInfo;
} OesOptSettlementConfirmReqT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_OPT_SETTLEMENT_CONFIRM_REQ {0}, {0}
/* -------------------------           */

/**
 * 期权账户结算单确认应答报文
 */
typedef OesOptSettlementConfirmBaseInfoT OesOptSettlementConfirmRspT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_OPT_SETTLEMENT_CONFIRM_RSP                                 \
  NULLOBJ_OPT_SETTLEMENT_CONFIRM_BASE_INFO
/* -------------------------           */

/* ===================================================================
 * 回报消息报文定义
 * =================================================================== */

/**
 * 回报消息的消息头定义
 */
typedef struct _OesRptMsgHead {
  int64 rptSeqNum; /**< 回报消息的编号 */

  uint8 rptMsgType; /**< 回报消息的消息代码 @see eOesMsgTypeT */
  uint8 execType;   /**< 执行类型 @see eOesExecTypeT */
  int16 bodyLength; /**< 回报消息的消息体大小 */

  int32 ordRejReason; /**< 订单/撤单被拒绝原因 */
} OesRptMsgHeadT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_RPT_MSG_HEAD 0, 0, 0, 0, 0
/* -------------------------           */

/**
 * 回报消息的消息体定义
 */
typedef union _OesRptMsgBody {
  OesOrdCnfmT ordInsertRsp;   /**< OES委托响应-委托已生成 */
  OesOrdRejectT ordRejectRsp; /**< OES委托响应-业务拒绝 */

  OesOrdCnfmT ordCnfm; /**< 交易所委托回报 */
  OesTrdCnfmT trdCnfm; /**< 交易所成交回报 */

  OesFundTrsfRejectT fundTrsfRejectRsp; /**< 出入金委托拒绝 */
  OesFundTrsfReportT fundTrsfCnfm;      /**< 出入金执行报告 */

  OesCashAssetReportT cashAssetRpt;   /**< 资金变动回报信息 */
  OesStkHoldingReportT stkHoldingRpt; /**< 持仓变动回报信息 (股票) */
  OesOptHoldingReportT optHoldingRpt; /**< 持仓变动回报信息 (期权) */
  OesOptUnderlyingHoldingReportT
      optUnderlyingHoldingRpt; /**< 期权标的持仓变动回报信息 */

  OesNotifyInfoReportT notifyInfoRpt; /**< 通知消息回报信息 */
  OesOptSettlementConfirmReportT
      optSettlementConfirmRpt; /**< 期权账户结算单确认回报信息 */

  OesCrdCashRepayReportT crdDebtCashRepayRpt;   /**< 融资融券直接还款执行报告 */
  OesCrdDebtContractReportT crdDebtContractRpt; /**< 融资融券合约变动回报信息 */
  OesCrdDebtJournalReportT crdDebtJournalRpt;   /**< 融资融券合约流水回报信息 */
} OesRptMsgBodyT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_RPT_MSG_BODY {NULLOBJ_OES_ORD_CNFM}
/* -------------------------           */

/**
 * 完整的回报消息定义
 */
typedef struct _OesRptMsg {
  OesRptMsgHeadT rptHead; /**< 回报消息的消息头 */
  OesRptMsgBodyT rptBody; /**< 回报消息的消息体 */
} OesRptMsgT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_RPT_MSG                                                    \
  {NULLOBJ_OES_RPT_MSG_HEAD}, { NULLOBJ_OES_RPT_MSG_BODY }
/* -------------------------           */

/* ===================================================================
 * 汇总的请求/应答消息定义 (除了查询消息以外的所有其它消息)
 * =================================================================== */

/**
 * 汇总的请求消息的消息体定义
 */
typedef union _OesReqMsgBody {
  /** 委托申报请求报文 */
  OesOrdReqT ordReq;

  /** 撤单请求请求报文 */
  OesOrdCancelReqT ordCancelReq;

  /** 批量委托请求报文 */
  OesBatchOrdersReqT batchOrdersReq;

  /** 融资融券负债归还(除直接还款以外)请求报文 */
  OesCrdRepayReqT crdRepayReq;

  /** 融资融券直接还款请求报文 */
  OesCrdCashRepayReqT crdCashRepayReq;

  /** 出入金请求报文 */
  OesFundTrsfReqT fundTrsfReq;

  /** 修改密码请求报文 */
  OesChangePasswordReqT changePasswordReq;

  /** 期权账户结算单确认请求报文 */
  OesOptSettlementConfirmReqT optSettlementConfirmReq;

  /** 测试请求报文 */
  OesTestRequestReqT testRequestReq;

  /** 回报同步请求报文 */
  OesReportSynchronizationReqT rptSyncReq;
} OesReqMsgBodyT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_REQ_MSG_BODY {NULLOBJ_OES_ORD_REQ}
/* -------------------------           */

/**
 * 汇总的应答消息的消息体定义
 */
typedef union _OesRspMsgBody {
  /** 执行报告回报消息 */
  OesRptMsgT rptMsg;

  /** 市场状态消息 */
  OesMarketStateInfoT mktStateRpt;

  /** 测试请求的应答报文 */
  OesTestRequestRspT testRequestRsp;

  /** 回报同步应答报文 */
  OesReportSynchronizationRspT reportSynchronizationRsp;

  /** 修改密码应答报文 */
  OesChangePasswordRspT changePasswordRsp;

  /** 结算单确认应答报文 */
  OesOptSettlementConfirmRspT optSettlementConfirmRsp;
} OesRspMsgBodyT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_RSP_MSG_BODY {NULLOBJ_OES_RPT_MSG}
/* -------------------------           */

/* ===================================================================
 * 统一的查询消息定义
 * =================================================================== */

/**
 * 统一的查询请求消息定义
 */
typedef union _OesQryReqMsg {
  OesQryOrdReqT qryOrd;             /**< 查询委托信息请求 */
  OesQryTrdReqT qryTrd;             /**< 查询成交信息请求 */
  OesQryCashAssetReqT qryCashAsset; /**< 查询客户资金信息请求 */
  OesQryColocationPeerCashReqT
      qryColoPeerCash; /**< 查询两地交易COLO对端结点的资金信息请求 */
  OesQryStkHoldingReqT qryStkHolding;       /**< 查询股票持仓信息请求 */
  OesQryOptHoldingReqT qryOptHolding;       /**< 查询期权持仓信息请求 */
  OesQryCustReqT qryCust;                   /**< 查询客户信息请求 */
  OesQryInvAcctReqT qryInvAcct;             /**< 查询证券账户请求 */
  OesQryCommissionRateReqT qryComms;        /**< 查询客户佣金信息请求 */
  OesQryFundTransferSerialReqT qryFundTrsf; /**< 查询出入金信息请求 */
  OesQryLotWinningReqT qryLotWinning;       /**< 查询新股配号、中签信息请求 */
  OesQryIssueReqT qryIssue;                 /**< 查询证券发行信息请求 */
  OesQryStockReqT qryStock;                 /**< 查询现货产品信息请求 */
  OesQryEtfReqT qryEtf;                     /**< 查询ETF申赎产品信息请求 */
  OesQryEtfComponentReqT qryEtfComponent;   /**< 查询ETF基金成份证券信息请求 */
  OesQryOptionReqT qryOption;               /**< 查询期权产品信息请求 */
  OesQryMarketStateReqT qryMktState;        /**< 查询市场状态信息请求 */
  OesQryNotifyInfoReqT qryNotifyInfo;       /**< 查询通知消息请求 */
  OesQryCounterCashReqT qryCounterCash;     /**< 查询主柜资金信息请求 */
  OesQryOptPositionLimitReqT
      qryOptPositionLimit; /**< 查询期权限仓额度信息请求 */
  OesQryOptPurchaseLimitReqT
      qryOptPurchaseLimit; /**< 查询期权限购额度信息请求 */
  OesQryOptUnderlyingHoldingReqT
      qryOptUnderlyingHolding; /**< 查询期权标的持仓信息请求 */
  OesQryOptExerciseAssignReqT
      qryOptExerciseAssign; /**< 查询期权行权指派信息请求 */

  /**
   * 信用类查询请求
   */
  OesQryCrdDebtContractReqT qryCrdDebtContract; /**< 查询融资融券合约信息请求 */
  OesQryCrdSecurityDebtStatsReqT
      qryCrdCustSecuDebtStats; /**< 查询客户单证券融资融券负债统计信息请求 */
  OesQryCrdCreditAssetReqT qryCrdCreditAsset; /**< 查询信用资产信息请求 */
  OesQryCrdCashRepayReqT
      qryCrdCashRepay; /**< 查询融资融券业务直接还券信息请求 */
  OesQryCrdCashPositionReqT
      qryCrdCashPosition; /**< 查询融资融券业务资金头寸信息 (可融资头寸信息)
                             请求 */
  OesQryCrdSecurityPositionReqT
      qryCrdSecurityPosition; /**< 查询融资融券业务证券头寸信息 (可融券头寸信息)
                                 请求 */
  OesQryCrdExcessStockReqT
      qryCrdExcessStock; /**< 查询融资融券业务余券信息请求 */
  OesQryCrdDebtJournalReqT
      qryCrdDebtJournal; /**< 查询融资融券合约流水信息请求 */
  OesQryCrdInterestRateReqT
      qryCrdInterestRateReq; /**< 查询融资融券息费利率请求 */
  OesQryCrdUnderlyingInfoReqT qryCrdUnderlyingInfoReq; /**<
                                                          查询融资融券可充抵保证金证券及融资融券标的信息请求
                                                        */
  OesQryCrdDrawableBalanceReqT
      qryCrdDrawableBalanceReq; /**< 查询融资融券业务可取资金的请求 */
  OesQryCrdCollateralTransferOutMaxQtyReqT
      qryCrdTransferOutMaxQtyReq; /**< 查询融资融券担保品可转出的最大数量请求 */
} OesQryReqMsgT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_REQ_MSG {NULLOBJ_OES_QRY_ORD_REQ}
/* -------------------------           */

/**
 * 统一的查询应答消息定义
 */
typedef union _OesQryRspMsg {
  OesQryOrdRspT ordRsp;             /**< 查询委托信息应答 */
  OesQryTrdRspT trdRsp;             /**< 查询成交信息应答 */
  OesQryCashAssetRspT cashAssetRsp; /**< 查询客户资金信息应答 */
  OesQryColocationPeerCashRspT
      qryColoPeerCashRsp; /**< 查询两地交易COLO对端结点的资金信息应答 */
  OesQryStkHoldingRspT stkHoldingRsp;       /**< 查询股票持仓信息应答 */
  OesQryOptHoldingRspT optHoldingRsp;       /**< 查询期权持仓信息应答 */
  OesQryCustRspT custRsp;                   /**< 查询客户信息应答 */
  OesQryInvAcctRspT invAcctRsp;             /**< 查询证券账户应答 */
  OesQryCommissionRateRspT commsRateRsp;    /**< 查询客户佣金信息应答 */
  OesQryFundTransferSerialRspT fundTrsfRsp; /**< 查询出入金流水信息应答 */
  OesQryLotWinningRspT lotWinningRsp;       /**< 查询新股配号、中签信息应答 */
  OesQryIssueRspT issueRsp;                 /**< 查询证券发行信息应答 */
  OesQryStockRspT stockRsp;                 /**< 查询现货产品信息应答 */
  OesQryEtfRspT etfRsp;                     /**< 查询ETF申赎产品信息应答 */
  OesQryEtfComponentRspT etfComponentRsp;   /**< 查询ETF基金成份证券信息应答 */
  OesQryOptionRspT optionRsp;               /**< 查询期权产品信息应答 */
  OesQryTradingDayRspT tradingDay;          /**< 查询当前交易日信息应答 */
  OesQryMarketStateRspT mktStateRsp;        /**< 查询市场状态信息应答 */
  OesQryNotifyInfoRspT notifyInfoRsp;       /**< 查询通知消息应答 */
  OesClientOverviewT clientOverview;        /**< 客户端总览信息 */
  OesQryCounterCashRspT counterCashRsp;     /**< 客户主柜资金信息 */
  OesQryOptPositionLimitRspT
      optPositionLimitRsp; /**< 查询期权限仓额度信息应答 */
  OesQryOptPurchaseLimitRspT
      optPurchaseLimitRsp; /**< 查询期权限购额度信息应答 */
  OesQryOptUnderlyingHoldingRspT
      optUnderlyingHoldingRsp; /**< 查询期权标的持仓信息应答 */
  OesQryOptExerciseAssignRspT
      optExerciseAssignRsp;                   /**< 查询期权行权指派信息应答 */
  OesQryBrokerParamsInfoRspT brokerParamsRsp; /**< 查询券商参数信息应答 */
  OesQryApplUpgradeInfoRspT applUpgradeRsp;   /**< 周边应用升级信息 */

  /**
   * 信用类查询应答
   */
  OesQryCrdDebtContractRspT crdDebtContractRsp; /**< 查询融资融券合约信息应答 */
  OesQryCrdSecurityDebtStatsRspT
      crdCustSecuDebtStatsRsp; /**< 查询客户单证券融资融券负债统计信息应答 */
  OesQryCrdCreditAssetRspT crdCreditAssetRsp; /**< 查询信用资产信息应答 */
  OesQryCrdCashRepayRspT
      crdCashRepayRsp; /**< 查询融资融券业务直接还券信息应答 */
  OesQryCrdCashPositionRspT
      crdCashPositionRsp; /**< 查询融资融券业务资金头寸信息 (可融资头寸信息)
                             应答 */
  OesQryCrdSecurityPositionRspT
      crdSecurityPositionRsp; /**< 查询融资融券业务证券头寸信息 (可融券头寸信息)
                                 应答 */
  OesQryCrdExcessStockRspT
      crdExcessStockRsp; /**< 查询融资融券业务余券信息应答 */
  OesQryCrdDebtJournalRspT
      crdDebtJournalRsp; /**< 查询融资融券合约流水信息应答 */
  OesQryCrdInterestRateRspT crdInterestRateRsp; /**< 查询融资融券息费利率应答 */
  OesQryCrdUnderlyingInfoRspT crdCustUnderlyingInfoRsp; /**<
                                                           查询融资融券可充抵保证金证券及融资融券标的信息应答
                                                         */
  OesQryCrdDrawableBalanceRspT
      crdDrawableBalanceRsp; /**< 查询融资融券业务可取资金的应答 */
  OesQryCrdCollateralTransferOutMaxQtyRspT
      crdTransferOutMaxQtyRsp; /**< 查询融资融券担保品及标的应答 */
} OesQryRspMsgT;

/* 结构体的初始化值定义 */
#define NULLOBJ_OES_QRY_RSP_MSG {NULLOBJ_OES_QRY_ORD_RSP}
/* -------------------------           */

#ifdef __cplusplus
}
#endif

#endif /* _OES_PACKETS_H */
