package com.google.android.games.paddleboat;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * Denotes that the annotated method or field can only be accessed when holding the referenced lock.
 * <p>
 * Example:
 * <pre>
 * final Object objectLock = new Object();
 *
 * {@literal @}GuardedBy("objectLock")
 * volatile Object object;
 *
 * Object getObject() {
 *     synchronized (objectLock) {
 *         if (object == null) {
 *             object = new Object();
 *         }
 *     }
 *     return object;
 * }</pre>
 */
@Target({ElementType.FIELD, ElementType.METHOD})
@Retention(RetentionPolicy.CLASS)
public @interface GuardedBy {
    String value();
}
