// Copyright (c) 2025 OUXT Polaris
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef PROTOLINK_DRIVERS__VISIBILITY_CONTROL_H_
#define PROTOLINK_DRIVERS__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define PROTOLINK_DRIVERS_EXPORT __attribute__((dllexport))
#define PROTOLINK_DRIVERS_IMPORT __attribute__((dllimport))
#else
#define PROTOLINK_DRIVERS_EXPORT __declspec(dllexport)
#define PROTOLINK_DRIVERS_IMPORT __declspec(dllimport)
#endif
#ifdef PROTOLINK_DRIVERS_BUILDING_LIBRARY
#define PROTOLINK_DRIVERS_PUBLIC PROTOLINK_DRIVERS_EXPORT
#else
#define PROTOLINK_DRIVERS_PUBLIC PROTOLINK_DRIVERS_IMPORT
#endif
#define PROTOLINK_DRIVERS_PUBLIC_TYPE PROTOLINK_DRIVERS_PUBLIC
#define PROTOLINK_DRIVERS_LOCAL
#else
#define PROTOLINK_DRIVERS_EXPORT __attribute__((visibility("default")))
#define PROTOLINK_DRIVERS_IMPORT
#if __GNUC__ >= 4
#define PROTOLINK_DRIVERS_PUBLIC __attribute__((visibility("default")))
#define PROTOLINK_DRIVERS_LOCAL __attribute__((visibility("hidden")))
#else
#define PROTOLINK_DRIVERS_PUBLIC
#define PROTOLINK_DRIVERS_LOCAL
#endif
#define PROTOLINK_DRIVERS_PUBLIC_TYPE
#endif

#endif  // PROTOLINK_DRIVERS__VISIBILITY_CONTROL_H_
