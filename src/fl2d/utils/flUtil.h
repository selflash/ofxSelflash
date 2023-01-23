#pragma once

#include "flObject.h"
#include "flInteractiveObject.h"
#include "flDisplayObject.h"
#include "flDisplayObjectContainer.h"
#include "flSprite.h"
#include "flShape.h"

namespace fl2d {
	class flUtil {

		public:
			//--------------------------------------------------------------
			static inline bool isInteractiveObject(flDisplayObject* displayObject) {
				if (displayObject == NULL) return false;

				bool b = false;
				b = b || (displayObject->typeID() == FL_TYPE_INTERACTIVE_OBJECT);
				b = b || (displayObject->typeID() == FL_TYPE_TEXT_FIELD);
				b = b || (displayObject->typeID() == FL_TYPE_DISPLAY_OBJECT_CONTAINER);
				b = b || (displayObject->typeID() == FL_TYPE_SPRITE);
				b = b || (displayObject->typeID() == FL_TYPE_MOVIE_CLIP);
				b = b || (displayObject->typeID() == FL_TYPE_UIBASE);

				return b;
			}

			//--------------------------------------------------------------
			static inline bool isDisplayObject(flDisplayObject* displayObject) {
				if (displayObject == NULL) return false;

				bool b = false;
				b = b || (displayObject->typeID() == FL_TYPE_SHAPE);
				b = b || (displayObject->typeID() == FL_TYPE_BITMAP);
				b = b || (displayObject->typeID() == FL_TYPE_SPRITE);
				b = b || (displayObject->typeID() == FL_TYPE_MOVIE_CLIP);
				b = b || (displayObject->typeID() == FL_TYPE_TEXT_FIELD);
				b = b || (displayObject->typeID() == FL_TYPE_UIBASE);

				return b;
			}

			//--------------------------------------------------------------
			static inline bool isDisplayObjectContainer(flDisplayObject* displayObject) {
				if (displayObject == NULL) return false;

				bool b = false;
				b = b || (displayObject->typeID() == FL_TYPE_DISPLAY_OBJECT_CONTAINER);
				b = b || (displayObject->typeID() == FL_TYPE_SPRITE);
				b = b || (displayObject->typeID() == FL_TYPE_MOVIE_CLIP);
				b = b || (displayObject->typeID() == FL_TYPE_UIBASE);

				return b;
			}

			//--------------------------------------------------------------
			static inline bool isSprite(flDisplayObject* displayObject) {
				if (displayObject == NULL) return false;

				bool b = false;
				b = b || (displayObject->typeID() == FL_TYPE_SPRITE);
				b = b || (displayObject->typeID() == FL_TYPE_MOVIE_CLIP);
				b = b || (displayObject->typeID() == FL_TYPE_UIBASE);

				return b;
			}

			//--------------------------------------------------------------
			static inline bool isShape(flDisplayObject* displayObject) {
				if (displayObject == NULL) return false;

				bool b = false;
				b = b || (displayObject->typeID() == FL_TYPE_SHAPE);

				return b;
			}

			//--------------------------------------------------------------
			static inline bool isGraphicalObject(flDisplayObject* displayObject) {
				if (displayObject == NULL) return false;

				bool b = false;
				b = b || (displayObject->typeID() == FL_TYPE_SHAPE);
				b = b || (displayObject->typeID() == FL_TYPE_SPRITE);

				return b;
			}

		private:
			flUtil() { };
			~flUtil() { };
	};

}