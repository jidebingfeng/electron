// Copyright (c) 2018 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/api/atom_api_box_layout.h"

#include "atom/common/api/constructor.h"
#include "native_mate/dictionary.h"

#include "atom/common/node_includes.h"

namespace mate {

template <>
struct Converter<views::BoxLayout::Orientation> {
  static bool FromV8(v8::Isolate* isolate,
                     v8::Handle<v8::Value> val,
                     views::BoxLayout::Orientation* out) {
    std::string orientation;
    if (!ConvertFromV8(isolate, val, &orientation))
      return false;
    if (orientation == "horizontal")
      *out = views::BoxLayout::kHorizontal;
    else if (orientation == "vertical")
      *out = views::BoxLayout::kVertical;
    else
      return false;
    return true;
  }
};

}  // namespace mate

namespace atom {

namespace api {

BoxLayout::BoxLayout(views::BoxLayout::Orientation orientation)
    : LayoutManager(new views::BoxLayout(orientation)) {}

BoxLayout::~BoxLayout() {}

// static
mate::WrappableBase* BoxLayout::New(mate::Arguments* args,
                                    views::BoxLayout::Orientation orientation) {
  auto* layout = new BoxLayout(orientation);
  layout->InitWith(args->isolate(), args->GetThis());
  return layout;
}

// static
void BoxLayout::BuildPrototype(v8::Isolate* isolate,
                               v8::Local<v8::FunctionTemplate> prototype) {}

}  // namespace api

}  // namespace atom

namespace {

using atom::api::BoxLayout;

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  v8::Isolate* isolate = context->GetIsolate();
  mate::Dictionary dict(isolate, exports);
  dict.Set("BoxLayout", mate::CreateConstructor<BoxLayout>(
                            isolate, base::Bind(&BoxLayout::New)));
}

}  // namespace

NODE_BUILTIN_MODULE_CONTEXT_AWARE(atom_browser_box_layout, Initialize)
