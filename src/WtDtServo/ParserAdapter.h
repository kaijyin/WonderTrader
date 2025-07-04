﻿/*!
 * \file ParserAdapter.h
 * \project	WonderTrader
 *
 * \author Wesley
 * \date 2020/03/30
 *
 * \brief 行情解析模块适配类定义
 */
#pragma once
#include "../Includes/IParserApi.h"
#include <boost/core/noncopyable.hpp>
#include <memory>
#include <set>
#include <vector>

NS_WTP_BEGIN
class WTSVariant;
NS_WTP_END

USING_NS_WTP;
class WTSBaseDataMgr;
class WtDtRunner;

class ParserAdapter : public IParserSpi, private boost::noncopyable {
public:
  ParserAdapter(WTSBaseDataMgr *bgMgr, WtDtRunner *runner);
  ~ParserAdapter();

public:
  bool init(const char *id, WTSVariant *cfg);

  bool initExt(const char *id, IParserApi *api);

  void release();

  bool run();

  const char *id() const { return _id.c_str(); }

public:
  virtual void handleSymbolList(const WTSArray *aySymbols) override;

  virtual void handleQuote(WTSTickData *quote, uint32_t procFlag) override;

  virtual void handleOrderQueue(WTSOrdQueData *ordQueData) override;

  virtual void handleTransaction(WTSTransData *transData) override;

  virtual void handleOrderDetail(WTSOrdDtlData *ordDetailData) override;

  virtual void handleParserLog(WTSLogLevel ll, const char *message) override;

  virtual IBaseDataMgr *getBaseDataMgr() override;

private:
  IParserApi *_parser_api;
  FuncDeleteParser _remover;
  WTSBaseDataMgr *_bd_mgr;
  WtDtRunner *_dt_runner;

  bool _stopped;

  typedef wt_hashset<std::string> ExchgFilter;
  ExchgFilter _exchg_filter;
  ExchgFilter _code_filter;
  WTSVariant *_cfg;
  std::string _id;
};

typedef std::shared_ptr<ParserAdapter> ParserAdapterPtr;
typedef wt_hashmap<std::string, ParserAdapterPtr> ParserAdapterMap;

class ParserAdapterMgr : private boost::noncopyable {
public:
  void release();

  void run();

  ParserAdapterPtr getAdapter(const char *id);

  bool addAdapter(const char *id, ParserAdapterPtr &adapter);

  uint32_t size() const { return (uint32_t)_adapters.size(); }

public:
  ParserAdapterMap _adapters;
};
